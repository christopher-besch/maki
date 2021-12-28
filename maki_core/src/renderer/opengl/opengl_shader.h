#pragma once

#include "../shader.h"

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace Maki {

class OpenGLShader: public Shader {
public:
    OpenGLShader(const std::string& vert_path, const std::string& frag_path);
    ~OpenGLShader();

    virtual void set_float1(const std::string& name, float val) override;
    virtual void set_float2(const std::string& name, const vec2& val) override;
    virtual void set_float3(const std::string& name, const vec3& val) override;
    virtual void set_float4(const std::string& name, const vec4& val) override;
    virtual void set_mat3(const std::string& name, const mat3& val) override;
    virtual void set_mat4(const std::string& name, const mat4& val) override;
    virtual void set_int1(const std::string& name, int val) override;

    virtual void bind() const override;
    virtual void unbind() const override;

private:
    void        compile(const std::unordered_map<GLenum, std::string>& shader_sources);
    std::string read_file(const std::string& path);

private:
    uint32_t m_id;
};

} // namespace Maki
