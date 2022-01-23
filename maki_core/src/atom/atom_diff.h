#pragma once

#include <glm/glm.hpp>

#include "atom/atom.h"

namespace Maki {

// only to be created by control thread
// immutable -> can't be changed by render thread -> no mutexes required

// how to convert single atom "across" frame-border
template<typename AtomType>
class AtomDiff {
public:
    explicit AtomDiff(uint32_t id)
        : m_id(id), m_priority(s_next_priority++) {}

    virtual ~AtomDiff() = default;

    uint32_t get_id() const { return m_id; }
    uint32_t get_priority() const { return m_priority; }

    virtual void apply(AtomType& atom) const   = 0;
    virtual void reverse(AtomType& atom) const = 0;

private:
    const uint32_t m_id;
    const uint32_t m_priority;

private:
    static uint32_t s_next_priority;
};

template<typename AtomType>
uint32_t AtomDiff<AtomType>::s_next_priority {0};

// used for sorting containers
template<typename AtomType>
class CompareAtomDiff {
public:
    bool operator()(const AtomDiff<AtomType>* a, const AtomDiff<AtomType>* b) const
    {
        if(a->get_id() < b->get_id())
            return true;
        if(a->get_id() > b->get_id())
            return false;
        // consult priority when id same
        if(a->get_priority() <= b->get_priority())
            return true;
        return false;
    }
};

template<typename AtomType>
class ToggleRenderDiff: public AtomDiff<AtomType> {
public:
    explicit ToggleRenderDiff(uint32_t id)
        : AtomDiff<AtomType> {id} {}

    virtual void apply(AtomType& atom) const override
    {
        atom.render = !atom.render;
    }
    virtual void reverse(AtomType& atom) const override
    {
        atom.render = !atom.render;
    }
};

// template<typename AtomType>
// class ReplacementDiff: public AtomDiff<AtomType> {
// public:
//     ReplacementDiff(uint32_t id)
//         : AtomDiff<AtomType>(id) {}

//     virtual void apply(AtomType& atom) const override
//     {
//         atom += m_diff;
//     }
//     virtual void reverse(AtomType& atom) const override
//     {
//         atom -= m_diff;
//     }

// private:
//     AtomType m_diff;
// };

template<typename AtomType>
class TransformDiff: public AtomDiff<AtomType> {
public:
    TransformDiff(uint32_t id, mat4 mat)
        : AtomDiff<AtomType> {id}, m_mat(mat)
    {
        m_inv_mat = glm::inverse(mat);
    }

    virtual void apply(AtomType& atom) const override
    {
        for(vec3& pos: atom.ver_pos) {
            pos = m_mat * vec4(pos, 1.0f);
        }
    }
    virtual void reverse(AtomType& atom) const override
    {
        for(vec3& pos: atom.ver_pos) {
            pos = m_inv_mat * vec4(pos, 1.0f);
        }
    }

private:
    mat4 m_mat;
    mat4 m_inv_mat;
};

template<typename AtomType>
class ReColorDiff: public AtomDiff<AtomType> {
public:
    ReColorDiff(uint32_t id, std::array<vec4, AtomType::vertex_count> delta_col)
        : AtomDiff<AtomType> {id}, m_delta_col {delta_col} {}

    virtual void apply(AtomType& atom) const override
    {
        atom.add_col(m_delta_col);
    }
    virtual void reverse(AtomType& atom) const override
    {
        atom.sub_col(m_delta_col);
    }

private:
    std::array<vec4, AtomType::vertex_count> m_delta_col;
};

} // namespace Maki
