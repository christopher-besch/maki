cmake_minimum_required(VERSION 3.10)

project(maki)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# required for spdlog included in a shared lib
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# dependencies
add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/glfw")

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/glm")

find_package(GLEW REQUIRED)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

set(STB_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/vendor/stb")

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/spdlog")

add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/pybind11")

# use warnings and multi threading
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} /MP2 /DWIN32_LEAN_AND_MEAN /DNOMINMAX"
  )
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/maki_core")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/maki")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
