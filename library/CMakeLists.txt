cmake_minimum_required (VERSION 3.22)

project ("library")

# 获取当前源代码目录的绝对路径
get_filename_component(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

# 遍历当前路径下的文件夹
file(GLOB __LIBRARY_INCLUDES__ "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(INCLUDE_DIR ${__LIBRARY_INCLUDES__})
  if(IS_DIRECTORY ${INCLUDE_DIR})
    # 替换掉绝对路径，只保留相对路径
    string(REPLACE "${SOURCE_DIR}/" "" RELATIVE_PATH ${INCLUDE_DIR})

    # 添加子项目
    add_subdirectory(${RELATIVE_PATH})
    unset(RELATIVE_PATH)
  endif()
endforeach()

unset(SOURCE_DIR)
unset(__LIBRARY_INCLUDES__)