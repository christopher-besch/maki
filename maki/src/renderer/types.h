#pragma once

#include "core/log.h"

namespace Maki {

enum class DataType {
    none = 0,
    float1,
    float2,
    float3,
    float4,
    mat3,
    mat4,
    int1,
    int2,
    int3,
    int4,
    bool1
};

inline size_t data_type_size(DataType type)
{
    switch(type) {
    case DataType::float1:
        return sizeof(float) * 1;
    case DataType::float2:
        return sizeof(float) * 2;
    case DataType::float3:
        return sizeof(float) * 3;
    case DataType::float4:
        return sizeof(float) * 4;
    case DataType::mat3:
        return sizeof(float) * 3 * 3;
    case DataType::mat4:
        return sizeof(float) * 4 * 4;
    case DataType::int1:
        return sizeof(int) * 1;
    case DataType::int2:
        return sizeof(int) * 2;
    case DataType::int3:
        return sizeof(int) * 3;
    case DataType::int4:
        return sizeof(int) * 4;
    case DataType::bool1:
        return sizeof(bool) * 1;
    default:
        MAKI_RAISE_CRITICAL("Unknown DataType.");
        return 0;
    }
}

inline uint32_t data_type_components(DataType type)
{
    switch(type) {
    case DataType::float1:
        return 1;
    case DataType::float2:
        return 2;
    case DataType::float3:
        return 3;
    case DataType::float4:
        return 4;
    case DataType::mat3:
        return 3 * 3;
    case DataType::mat4:
        return 4 * 4;
    case DataType::int1:
        return 1;
    case DataType::int2:
        return 2;
    case DataType::int3:
        return 3;
    case DataType::int4:
        return 4;
    case DataType::bool1:
        return 1;
    default:
        MAKI_RAISE_CRITICAL("Unknown DataType.");
        return 0;
    }
}

} // namespace Maki
