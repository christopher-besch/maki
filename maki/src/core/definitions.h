#pragma once

#include <chrono>
#include <math.h>

#include <glm/glm.hpp>

namespace Maki {

// definitions
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

using mat3 = glm::mat3;
using mat4 = glm::mat4;

// consts
constexpr float PI {M_PI};

using Clock     = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>>;
using Duration  = std::chrono::duration<long, std::ratio<1, 1000000000>>;

inline long get_mills(Duration duration)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

} // namespace Maki
