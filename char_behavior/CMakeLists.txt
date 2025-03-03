cmake_minimum_required (VERSION 3.22)

project ("run")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
else()
    # 通用编译选项
    if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGCXX)
        # GCC and Clang

        # 链接器优化
        # -ffunction-sections 和 -fdata-sections:
        # 这些选项会将每个函数和数据段放入独立的段中,从而在链接时可以更容易地剔除未使用的代码段
        # 与 -Wl,--gc-sections 配合使用时，链接器会删除未被使用的部分代码
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

        # --as-needed 只在必要时才包含动态库的符号
        # --strip-all 删除不必要的符号
        # --gc-sections 移除未使用的符号
        # --sort-common 将相同的数据段合并在一起以减少内存占用
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-O3 -Wl,--strip-all -Wl,--as-needed -Wl,--gc-sections -Wl,--sort-common")
    elseif (MSVC)
        # MSVC
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /OPT:REF /OPT:ICF")
    endif()
    message(STATUS "Not building in Debug mode")
endif()

# 获取当前源代码目录的绝对路径
get_filename_component(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" ABSOLUTE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 三方库
find_package(nlohmann_json REQUIRED)
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIR})
# HTTPLIB
set(HTTPLIB_INCLUDE "${THIRD_PARTY_DIR}/httplib/include")
include_directories(${HTTPLIB_INCLUDE})

find_package(SFML 3 COMPONENTS Graphics Window Audio System Network REQUIRED)

# SFML_INCLUDE_DIRS为自定义的目录

set(SFML_DIR "C:/Program Files (x86)/SFML-3.0.0")

include_directories(${SFML_DIR}/include)
file(GLOB SFML_DLL "${SFML_DIR}/bin/*")
file(COPY ${SFML_DLL} DESTINATION "${PROJECT_ROOT_NODE}/bin")

# 遍历目录并将路径添加到 include_directories 中
foreach(INCLUDE_DIR ${LIBRARY_INCLUDES})
    if(IS_DIRECTORY ${INCLUDE_DIR})
        include_directories(${INCLUDE_DIR}/include)
    endif()
endforeach()

# 以当前目录为基准
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 指定最终的可执行文件的位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_NODE}/bin)

# 将源代码添加到此项目的可执行文件。
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 图标设置
file(COPY "${PROJECT_ROOT_NODE}/favicon.png" DESTINATION "${PROJECT_ROOT_NODE}/bin")

set(ICON_LOAD "")
if(WIN32)
    set(APP_ICON_RESOURCE "${PROJECT_ROOT_NODE}/app_icon.rc")

    # 使用 windres 编译资源文件
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/app_icon.o
            COMMAND windres -i ${APP_ICON_RESOURCE} -o ${CMAKE_CURRENT_BINARY_DIR}/app_icon.o -O coff
            MAIN_DEPENDENCY ${APP_ICON_RESOURCE}
    )

    set(ICON_LOAD "${CMAKE_CURRENT_BINARY_DIR}/app_icon.o")
endif()

add_executable(${PROJECT_NAME} ${SRC_LIST} ${ICON_LOAD})

# 添加多个CPP/HPP/H
set(sources)

file(GLOB_RECURSE sources_glob "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach (source ${sources_glob})
    string(REPLACE "${SOURCE_DIR}/" "" RELATIVE_PATH ${source})
    if (NOT(${RELATIVE_PATH} STREQUAL "main.cpp"))
        list(APPEND sources "${source}")
    endif ()

    unset(RELATIVE_PATH)
endforeach ()

target_sources(${PROJECT_NAME} PUBLIC ${sources})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json yaml-cpp::yaml-cpp
SFML::Graphics SFML::Audio SFML::Network SFML::Window core)

# 给Windows项目添加图标
if(WIN32)
    message(STATUS "Configuring for Windows")
    # Windows-specific compile options
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DPLATFORM_WINDOWS)
endif()

unset(SOURCE_DIR)
unset(sources_glob)
unset(sources)

message(PROJECT:${PROJECT_NAME},G:${CMAKE_C_COMPILER_VERSION},GXX:${CMAKE_CXX_COMPILER_VERSION},CXX STANDARD:${CMAKE_CXX_STANDARD})
message(final)