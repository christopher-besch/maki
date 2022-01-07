#pragma once

#include <array>

#include "core/definitions.h"

namespace Maki {

// implementation inheritance only -> not to be used as an interface -> can be used on stack
// represent smallest renderable unit
struct Atom {
    bool render {false};
};

struct CuboidAtom: public Atom {
    std::array<vec3, 8> ver_pos {
        vec3 {-1.0f, -1.0f, +1.0f},  // 0 bottom front left
        vec3 {+1.0f, -1.0f, +1.0f},  // 1 bottom front right
        vec3 {-1.0f, -1.0f, -1.0f},  // 2 bottom back  left
        vec3 {+1.0f, -1.0f, -1.0f},  // 3 bottom back  right
        vec3 {-1.0f, +1.0f, +1.0f},  // 4 top    front left
        vec3 {+1.0f, +1.0f, +1.0f},  // 5 top    front right
        vec3 {-1.0f, +1.0f, -1.0f},  // 6 top    back  left
        vec3 {+1.0f, +1.0f, -1.0f}}; // 7 top    back  right
    std::array<vec4, 8> ver_col {
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f},
        vec4 {1.0f, 1.0f, 1.0f, 1.0f}};

    CuboidAtom& operator+=(const CuboidAtom& atom);
    CuboidAtom& operator-=(const CuboidAtom& atom);
    void        add_pos(const CuboidAtom& atom);
    void        add_col(const CuboidAtom& atom);
    void        sub_pos(const CuboidAtom& atom);
    void        sub_col(const CuboidAtom& atom);
};

} // namespace Maki
