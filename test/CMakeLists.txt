cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(test ${SOURCES})
target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
