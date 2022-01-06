#pragma once

#include <glm/glm.hpp>
#include <set>
#include <vector>

#include "core/definitions.h"

namespace Maki {

// atoms //
struct Atom {
    bool render;
};

struct CuboidAtom: public Atom {
    float ver_pos[3 * 8];
    float ver_col[3 * 8];
};

// atom differences //
template<typename T>
struct AtomDiff {
    using atom_type = T;

    uint32_t id;
};

template<typename T>
// can't cross atom type border
struct ReplacementDiff: public AtomDiff<T> {
    T new_atom;
};

template<typename T>
struct LinTransformDiff: public AtomDiff<T> {
    mat4 mat;
    mat4 inv_mat;

    LinTransformDiff(mat4 mat)
        : mat(mat)
    {
        inv_mat = glm::inverse(mat);
    }
};

// containers //
template<typename T>
class CompareAtom {
public:
    // to be rendered atoms first
    bool operator()(const T& a, const T&)
    {
        return a.render;
    }
};

template<typename T>
using AtomChain = std::multiset<T, CompareAtom<T>>;

// one entry per frame
template<typename T>
using AtomDiffs = std::vector<std::set<AtomDiff<T>*>>;

} // namespace Maki
