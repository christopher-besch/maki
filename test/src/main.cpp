#include "pch.h"

#include "controls.h"
#include "load_shader.h"
#include "load_texture.h"

int main()
{
    // initialise GLFW
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        getchar();
        return -1;
    }

    // 4x antialiasing
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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    // init glew
    glfwMakeContextCurrent(window);
    // init glfw
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // accept fragment if closer
    glDepthFunc(GL_LESS);

    GLuint program_id = load_shaders("res/shaders/simple_vertex.glsl", "res/shaders/simple_fragment.glsl");
    if(!program_id) {
        glfwTerminate();
        return -1;
    }

    // matrix uniform
    GLuint mvp_id = glGetUniformLocation(program_id, "mvp");

    // cube vertices
    const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    GLuint texture = load_texture("res/images/uvtemplate.tga");
    if(!texture) {
        glfwTerminate();
        return -1;
    }

    const GLfloat uv_buffer_data[] = {
        0.000059f, 1.0f - 0.000004f,
        0.000103f, 1.0f - 0.336048f,
        0.335973f, 1.0f - 0.335903f,
        1.000023f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.336024f, 1.0f - 0.671877f,
        0.667969f, 1.0f - 0.671889f,
        1.000023f, 1.0f - 0.000013f,
        0.668104f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.000059f, 1.0f - 0.000004f,
        0.335973f, 1.0f - 0.335903f,
        0.336098f, 1.0f - 0.000071f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.336024f, 1.0f - 0.671877f,
        1.000004f, 1.0f - 0.671847f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.668104f, 1.0f - 0.000013f,
        0.335973f, 1.0f - 0.335903f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.668104f, 1.0f - 0.000013f,
        0.336098f, 1.0f - 0.000071f,
        0.000103f, 1.0f - 0.336048f,
        0.000004f, 1.0f - 0.671870f,
        0.336024f, 1.0f - 0.671877f,
        0.000103f, 1.0f - 0.336048f,
        0.336024f, 1.0f - 0.671877f,
        0.335973f, 1.0f - 0.335903f,
        0.667969f, 1.0f - 0.671889f,
        1.000004f, 1.0f - 0.671847f,
        0.667979f, 1.0f - 0.335851f};

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    GLuint uv_buffer;
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);

    double  last_time = glfwGetTime();
    float   delta_time;
    Control ctrl;
    do {
        double current_time = glfwGetTime();
        delta_time          = current_time - last_time;
        last_time           = current_time;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program_id);

        mat4 projection, view;
        compute_mat_from_input(ctrl, delta_time, projection, view, window);

        mat4 model = mat4(1.0f);

        mat4 mvp = projection * view * model;

        glUniformMatrix4fv(mvp_id, 1, false, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
            0,                      // arbitrary id, must match shader
            3,                      // amount per vertex
            GL_FLOAT,               // type
            GL_FALSE,               // normalized
            0,                      // stride
            static_cast<void*>(0)); // array buffer offset
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glVertexAttribPointer(
            1,                      // arbitrary id, must match shader
            2,                      // amount per vertex
            GL_FLOAT,               // type
            GL_FALSE,               // normalized
            0,                      // stride
            static_cast<void*>(0)); // array buffer offset

        // draw
        // start at vertex, in total
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    // cleanup
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_id);
    glDeleteProgram(program_id);

    glfwTerminate();

    return 0;
}
