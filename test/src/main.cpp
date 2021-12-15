#include "pch.h"

int main()
{
    // 4x ntialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // for macos
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // disable old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // open window, create context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Hello World", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    // init glew
    glfwMakeContextCurrent(window);
    // init glfw
    glewExperimental = true;
    if(glfwInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
}
