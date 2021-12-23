#include "pch.h"

#include "shader.h"

OpenGLShader::OpenGLShader(const std::string& vert_path, const std::string& frag_path)
{
    std::string vert_source = read_file(vert_path);
    std::string frag_source = read_file(frag_path);

    compile({{GL_VERTEX_SHADER, vert_source},
             {GL_FRAGMENT_SHADER, frag_source}});
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_id);
}

void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shader_sources)
{
    m_id = glCreateProgram();

    // used to delete shaders once attached
    std::array<GLenum, 8> shader_ids;
    int                   shader_id_idx {0};

    for(auto& [type, source]: shader_sources) {
        uint32_t    shader       = glCreateShader(type);
        const char* source_c_str = source.c_str();
        glShaderSource(shader, 1, &source_c_str, nullptr);
        glCompileShader(shader);

        GLint is_compiled {0};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
        if(is_compiled == GL_FALSE) {
            int max_length {0};
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<char> log(max_length);
            glGetShaderInfoLog(shader, max_length, &max_length, &log[0]);

            std::cout << "Shader compilation failure: " << log.data() << std::endl;
        }
        glAttachShader(m_id, shader);
        shader_ids[shader_id_idx++] = shader;
    }

    glLinkProgram(m_id);

    GLint is_linked {0};
    glGetProgramiv(m_id, GL_LINK_STATUS, &is_linked);
    if(is_linked == GL_FALSE) {
        int max_length {0};
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<char> log(max_length);
        glGetProgramInfoLog(m_id, max_length, &max_length, &log[0]);

        std::cout << "Shader linkage failure: " << log.data() << std::endl;
    }

    for(int i {0}; i < shader_id_idx; ++i) {
        glDetachShader(m_id, shader_ids[i]);
        glDeleteShader(shader_ids[i]);
    }
}

std::string OpenGLShader::read_file(const std::string& path)
{
    std::string   out;
    std::ifstream stream(path, std::ios::in);
    if(stream.is_open()) {
        std::stringstream ss;
        ss << stream.rdbuf();
        out = ss.str();
        stream.close();
    }
    else
        std::cout << "Impossible to open " << path << std::endl;
    return out;
}

void OpenGLShader::set_float1(const std::string& name, float val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform1f(location, val);
}
void OpenGLShader::set_float2(const std::string& name, const vec2& val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform2f(location, val.x, val.y);
}
void OpenGLShader::set_float3(const std::string& name, const vec3& val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, val.x, val.y, val.z);
}
void OpenGLShader::set_float4(const std::string& name, const vec4& val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform4f(location, val.x, val.y, val.z, val.w);
}
void OpenGLShader::set_mat3(const std::string& name, const mat3& val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    // glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val));
}
void OpenGLShader::set_mat4(const std::string& name, const mat4& val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    // glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}
void OpenGLShader::set_int1(const std::string& name, int val)
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(location, val);
}

void OpenGLShader::bind() const
{
    glUseProgram(m_id);
}
void OpenGLShader::unbind() const
{
    glUseProgram(0);
}
