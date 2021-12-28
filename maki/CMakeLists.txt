cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
pybind11_add_module(maki ${SOURCES})
target_include_directories(maki PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(maki PRIVATE maki_core)
