cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(stub ${SOURCES})
target_include_directories(stub PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# dependencies
target_link_libraries(stub PRIVATE maki_core)
