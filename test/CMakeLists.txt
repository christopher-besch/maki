cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(test ${SOURCES})
target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")

target_link_libraries(test PRIVATE glfw)
target_link_libraries(test PRIVATE glm)
target_link_libraries(test PRIVATE ${OPENGL_LIBRARIES})

target_include_directories(test PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${GLEW_LIBRARIES})

# copy shaders in beginning
file(
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/"
)
# copy shaders before each build
add_custom_command(
  TARGET test
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
  "${CMAKE_CURRENT_BINARY_DIR}/shaders"
)
