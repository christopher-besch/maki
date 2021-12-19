cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(maki STATIC ${SOURCES})
target_include_directories(maki PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(maki PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
target_include_directories(maki INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# dependencies
target_link_libraries(maki PRIVATE glfw)

target_link_libraries(maki PRIVATE glm)

target_link_libraries(maki PRIVATE ${OPENGL_LIBRARIES})

target_include_directories(maki PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(maki PRIVATE ${GLEW_LIBRARIES})

target_include_directories(maki PRIVATE ${STB_INCLUDE_DIRS})

# copy resources in beginning
file(
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/res"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/"
)
# copy resources before each build
add_custom_command(
  TARGET maki
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res"
  "${CMAKE_CURRENT_BINARY_DIR}/res"
)
