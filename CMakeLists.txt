# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.22)

#vcpkg
# 手动设置到vcpkg根目录
# set(VCPKG_ROOT "D:/vcpkg")
# set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
#         CACHE STRING "Vcpkg toolchain file")
# set(VCPKG_TARGET_TRIPLET "x86-mingw-static" CACHE STRING "vcpkg package triplet")

set(PROJECT_ROOT_NODE ${CMAKE_CURRENT_SOURCE_DIR})
set(THIRD_PARTY_DIR "${PROJECT_ROOT_NODE}/3rdparty")

# 将指定目录文件所有复制到二进制文件目录
file(GLOB allCopyFiles  "${CMAKE_CURRENT_SOURCE_DIR}/resource/*")
# file(GLOB_RECURSE allCopyFiles  "${CMAKE_CURRENT_SOURCE_DIR}/resource/*")
file(COPY ${allCopyFiles} DESTINATION ${PROJECT_ROOT_NODE}/bin)

project ("CharAction")

file(GLOB LIBRARY_INCLUDES "${PROJECT_ROOT_NODE}/library/*")
# 包含子项目。
add_subdirectory(library)
add_subdirectory(char_behavior)