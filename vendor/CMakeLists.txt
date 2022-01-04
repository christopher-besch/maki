# glfw
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw")

# glm
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glm")

# stb
add_library(stb STATIC "${CMAKE_CURRENT_SOURCE_DIR}/stb.cpp")
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/stb")

# spdlog
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/spdlog")

# pybind11
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/pybind11")

# imgui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
add_library(
  imgui STATIC
  "${IMGUI_DIR}/imgui_demo.cpp"
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_tables.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/imgui.cpp"
  
  # backends
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(imgui PUBLIC "${IMGUI_DIR}" "${IMGUI_DIR}/backends")
target_include_directories(imgui INTERFACE "${IMGUI_DIR}/include")

target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(imgui PUBLIC ${OPENGL_LIBRARIES})
