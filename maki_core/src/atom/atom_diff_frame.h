#pragma once

#include <set>

#include "atom/atom_diff.h"
#include "core/log.h"

namespace Maki {

template<typename AtomType>
class AtomChain;

// all changes required to convert atoms of current frame into next or previous (apply or reverse)
template<typename AtomType>
class AtomDiffFrame {
public:
    AtomDiffFrame() = default;
    // copy not allowed
    AtomDiffFrame(const AtomDiffFrame<AtomType>&) = delete;
    AtomDiffFrame& operator=(const AtomDiffFrame<AtomType>&) = delete;

    AtomDiffFrame(AtomDiffFrame<AtomType>&& other)
        : m_atom_diffs {std::move(other.m_atom_diffs)}
    {
        other.m_atom_diffs.clear();
    }
    AtomDiffFrame& operator=(AtomDiffFrame<AtomType>&& other)
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs)
            delete atom_diff;
        m_atom_diffs = std::move(other.m_atom_diffs);
        other.m_atom_diffs.clear();
        return *this;
    }
    ~AtomDiffFrame()
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs)
            delete atom_diff;
    }

    void add(AtomDiff<AtomType>* new_atom_diff)
    {
        m_atom_diffs.insert(new_atom_diff);
    }

    void apply(std::vector<AtomType>& atoms) const
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs) {
            atom_diff->apply(atoms[atom_diff->get_id()]);
        }
    }
    void reverse(std::vector<AtomType>& atoms) const
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs) {
            atom_diff->reverse(atoms[atom_diff->get_id()]);
        }
    }

private:
    // sorted by id, then priority -> cache locality + correct order
    std::set<AtomDiff<AtomType>*, CompareAtomDiff<AtomType>> m_atom_diffs;
};

} // namespace Maki
