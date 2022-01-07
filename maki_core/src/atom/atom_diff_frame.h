#pragma once

#include <set>

#include "atom/atom_diff.h"
#include "core/log.h"

namespace Maki {

template<typename AtomType>
class AtomChain;

// all changes required to convert frame into last or next
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
        MAKI_LOG_WARN("destructing atom diff frame.");
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs)
            delete atom_diff;
        m_atom_diffs = std::move(other.m_atom_diffs);
        other.m_atom_diffs.clear();
    }
    ~AtomDiffFrame()
    {
        MAKI_LOG_WARN("destructing atom diff frame (size {}).", m_atom_diffs.size());
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs)
            delete atom_diff;
    }

    void add(AtomDiff<AtomType>* new_atom_diff)
    {
        m_atom_diffs.insert(new_atom_diff);
    }

    void apply(std::vector<AtomType>& atom_chain) const
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs) {
            atom_diff->apply(atom_chain[atom_diff->get_id()]);
        }
    }
    void reverse(std::vector<AtomType>& atom_chain) const
    {
        for(AtomDiff<AtomType>* atom_diff: m_atom_diffs) {
            atom_diff->reverse(atom_chain[atom_diff->get_id()]);
        }
    }

private:
    // sorted by id, then priority -> cache locality + correct order
    std::set<AtomDiff<AtomType>*, CompareAtomDiff<AtomType>> m_atom_diffs;
};

} // namespace Maki
