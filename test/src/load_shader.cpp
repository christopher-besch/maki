#include "pch.h"

#include "load_shader.h"

bool read_file(const char* path, std::string& out)
{
    std::ifstream stream(path, std::ios::in);
    if(stream.is_open()) {
        std::stringstream ss;
        ss << stream.rdbuf();
        out = ss.str();
        stream.close();
    }
    else {
        std::cerr << "Impossible to open '" << path << "'." << std::endl;
        return false;
    }
    return true;
}

bool compile_shader(GLuint id, std::string& code)
{
    const char* vert_code_ptr = code.c_str();
    glShaderSource(id, 1, &vert_code_ptr, nullptr);
    glCompileShader(id);

    // check shader
    GLint result = GL_FALSE;
    int   info_log_length;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
        std::vector<char> error_message(info_log_length + 1);
        glGetShaderInfoLog(id, info_log_length, nullptr, &error_message[0]);
        std::cerr << &error_message[0] << std::endl;
        return false;
    }
    return true;
}

GLuint load_shaders(const char* vert_path, const char* frag_path)
{
    // read files
    std::string vert_code;
    std::string frag_code;
    if(!read_file(vert_path, vert_code) || !read_file(frag_path, frag_code))
        return 0;

    // create shaders
    GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    // compile shaders
    std::cout << "Compiling shader: '" << vert_path << "'" << std::endl;
    if(!compile_shader(vert_id, vert_code))
        return 0;
    std::cout << "Compiling shader: '" << frag_path << "'" << std::endl;
    if(!compile_shader(frag_id, frag_code))
        return 0;

    // link program
    std::cout << "Linking program" << std::endl;
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vert_id);
    glAttachShader(program_id, frag_id);
    glLinkProgram(program_id);

    // check program
    GLint result = GL_FALSE;
    int   info_log_length;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
        std::vector<char> error_message(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, nullptr, &error_message[0]);
        std::cerr << &error_message[0] << std::endl;
        return 0;
    }

    glDetachShader(program_id, vert_id);
    glDetachShader(program_id, frag_id);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    return program_id;
}
