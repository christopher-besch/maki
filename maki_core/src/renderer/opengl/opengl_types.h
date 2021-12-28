#pragma once

#include "../types.h"

#include <GL/glew.h>

namespace Maki {

inline GLenum data_type_to_gl_enum(DataType type)
{
    switch(type) {
    case DataType::float1:
        return GL_FLOAT;
    case DataType::float2:
        return GL_FLOAT;
    case DataType::float3:
        return GL_FLOAT;
    case DataType::float4:
        return GL_FLOAT;
    case DataType::mat3:
        return GL_FLOAT;
    case DataType::mat4:
        return GL_FLOAT;
    case DataType::int1:
        return GL_INT;
    case DataType::int2:
        return GL_INT;
    case DataType::int3:
        return GL_INT;
    case DataType::int4:
        return GL_INT;
    case DataType::bool1:
        return GL_BOOL;
    default:
        MAKI_RAISE_CRITICAL("Unknown DataType.");
        return 0;
    }
}

} // namespace Maki
