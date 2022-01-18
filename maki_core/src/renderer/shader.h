#pragma once

#include <string>

#include "core/definitions.h"

namespace Maki {

// store shader and uniform definitions
class Shader {
public:
    static Shader* create(const std::string& vert_path, const std::string& frag_path);

public:
    virtual ~Shader() = default;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void set_float1(const std::string& name, float val)       = 0;
    virtual void set_float2(const std::string& name, const vec2& val) = 0;
    virtual void set_float3(const std::string& name, const vec3& val) = 0;
    virtual void set_float4(const std::string& name, const vec4& val) = 0;
    virtual void set_mat3(const std::string& name, const mat3& val)   = 0;
    virtual void set_mat4(const std::string& name, const mat4& val)   = 0;
    virtual void set_int1(const std::string& name, int val)           = 0;
};

} // namespace Maki
