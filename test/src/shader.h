#include "pch.h"
#include <unordered_map>

class OpenGLShader {
public:
    OpenGLShader(const std::string& vert_path, const std::string& frag_path);
    ~OpenGLShader();

    void set_float1(const std::string& name, float val);
    void set_float2(const std::string& name, const vec2& val);
    void set_float3(const std::string& name, const vec3& val);
    void set_float4(const std::string& name, const vec4& val);
    void set_mat3(const std::string& name, const mat3& val);
    void set_mat4(const std::string& name, const mat4& val);
    void set_int1(const std::string& name, int val);

    void bind() const;
    void unbind() const;

    uint32_t get_id() { return m_id; }

private:
    void        compile(const std::unordered_map<GLenum, std::string>& shader_sources);
    std::string read_file(const std::string& path);

private:
    uint32_t m_id;
};
