cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(sandbox ${SOURCES})
target_include_directories(sandbox PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# dependencies
target_link_libraries(sandbox PRIVATE maki_core)
