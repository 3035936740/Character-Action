cmake_minimum_required (VERSION 3.22)

project ("core")

# 强制采用C++23标准
set(CMAKE_CXX_STANDARD 23)

# 三方库

# 指定最终的DLL文件的位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_NODE}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 将源代码添加到此项目的可执行文件。
file(GLOB_RECURSE SRC_LIST 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/**.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

target_link_libraries(${PROJECT_NAME})

message(PROJECT:${PROJECT_NAME},G:${CMAKE_C_COMPILER_VERSION},GXX:${CMAKE_CXX_COMPILER_VERSION},CXX STANDARD:${CMAKE_CXX_STANDARD})
message(final)