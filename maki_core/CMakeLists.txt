cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(maki_core STATIC ${SOURCES})
target_include_directories(maki_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(maki_core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
target_include_directories(maki_core INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# dependencies
target_link_libraries(maki_core PUBLIC glfw)

target_link_libraries(maki_core PUBLIC glm)

target_link_libraries(maki_core PUBLIC ${OPENGL_LIBRARIES})

target_include_directories(maki_core PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(maki_core PUBLIC ${GLEW_LIBRARIES})

target_include_directories(maki_core PUBLIC ${STB_INCLUDE_DIRS})

target_link_libraries(maki_core PUBLIC spdlog)

# copy resources in beginning
message("-- Copying resources")
file(
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/res"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/"
)
# copy resources before each build
add_custom_command(
  TARGET maki_core
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res"
  "${CMAKE_CURRENT_BINARY_DIR}/res"
)
message("-- Copying resources - OK")

# platform config
set(platforms "glfw")
set(platform "none" CACHE STRING "Platform to be used, one of: ${platforms}")
set_property(CACHE platform PROPERTY STRINGS ${platforms})

if(NOT platform IN_LIST platforms)
  message(FATAL_ERROR "The platform must be one of: ${platforms}")
endif()
add_compile_definitions(PLATFORM=${platform})
