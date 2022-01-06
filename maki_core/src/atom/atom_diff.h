#pragma once

#include <glm/glm.hpp>

#include "atom/atom.h"

namespace Maki {

// how to convert atom "across" frame-border
template<typename T>
class AtomDiff {
public:
    AtomDiff(uint32_t id)
        : m_id(id) {}

    virtual void apply(T& atom) const   = 0;
    virtual void reverse(T& atom) const = 0;
    uint32_t     get_id() const { return m_id; }

    virtual ~AtomDiff() = default;

private:
    uint32_t m_id;

private:
    using s_atom_type = T;
};

template<typename T>
class ToggleRenderDiff: public AtomDiff<T> {
public:
    ToggleRenderDiff(uint32_t id)
        : AtomDiff<T>(id) {}

    virtual void apply(T& atom) const override
    {
        atom.render = !atom.render;
    }
    virtual void reverse(T& atom) const override
    {
        atom.render = !atom.render;
    }
};

template<typename T>
class ReplacementDiff: public AtomDiff<T> {
public:
    ReplacementDiff(uint32_t id)
        : AtomDiff<T>(id) {}

    virtual void apply(T& atom) const override
    {
        atom += m_diff;
    }
    virtual void reverse(T& atom) const override
    {
        atom -= m_diff;
    }

private:
    T m_diff;
};

template<typename T>
class TransformDiff: public AtomDiff<T> {
public:
    TransformDiff(uint32_t id)
        : AtomDiff<T>(id) {}

    TransformDiff(mat4 mat)
        : m_mat(mat)
    {
        m_inv_mat = glm::inverse(mat);
    }

    virtual void apply(T& atom) const override
    {
        for(size_t i {0}; i != atom.ver_pos; i += 3) {
            // TODO: should use move operations instead
            // TODO: fix code duplication
            vec4 ver_pos {
                atom.ver_pos[i + 0],
                atom.ver_pos[i + 1],
                atom.ver_pos[i + 2],
                1.0f};
            ver_pos             = m_mat * vec4();
            atom.ver_pos[i + 0] = ver_pos.x;
            atom.ver_pos[i + 1] = ver_pos.y;
            atom.ver_pos[i + 2] = ver_pos.z;
        }
    }
    virtual void reverse(T& atom) const override
    {
        for(size_t i {0}; i != atom.ver_pos; i += 3) {
            // TODO: should use move operations instead
            vec4 ver_pos {
                atom.ver_pos[i + 0],
                atom.ver_pos[i + 1],
                atom.ver_pos[i + 2],
                1.0f};
            ver_pos              = m_inv_mat * vec4();
            atom.ver_post[i + 0] = ver_pos.x;
            atom.ver_post[i + 1] = ver_pos.y;
            atom.ver_post[i + 2] = ver_pos.z;
        }
    }

private:
    mat4 m_mat;
    mat4 m_inv_mat;
};

} // namespace Maki
