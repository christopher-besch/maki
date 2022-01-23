#pragma once

#include <array>

#include "atom/atom.h"
#include "core/definitions.h"

namespace Maki {

struct QuadrilateralAtom: public Atom {
    std::array<vec3, 4> ver_pos {
        vec3 {-1.0f, -1.0f, +0.0f},  // bottom left
        vec3 {+1.0f, -1.0f, +0.0f},  // bottom right
        vec3 {-1.0f, +1.0f, +0.0f},  // top    left
        vec3 {+1.0f, +1.0f, +0.0f}}; // top    right
    std::array<vec4, 4> ver_col {
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f}};

    QuadrilateralAtom& operator+=(const QuadrilateralAtom& atom);
    QuadrilateralAtom& operator-=(const QuadrilateralAtom& atom);
    void               add_pos(const std::array<vec3, 4>& delta_pos);
    void               sub_pos(const std::array<vec3, 4>& delta_pos);
    void               add_col(const std::array<vec4, 4>& delta_col);
    void               sub_col(const std::array<vec4, 4>& delta_col);

    static constexpr uint32_t    vertex_count {8};
    static constexpr const char* type_name {"Quadrilateral"};
};

} // namespace Maki
