#pragma once

#include <set>
#include <vector>

#include "atom/atom.h"
#include "atom/atom_diff.h"
#include "core/log.h"

namespace Maki {

template<typename T>
class AtomChain;

template<typename T>
class AtomDiffFrame {
public:
    ~AtomDiffFrame()
    {
        for(AtomDiff<T>* atom_diff: m_atom_diffs)
            delete atom_diff;
    }

    void add(AtomDiff<T>* new_atom_diff)
    {
        m_atom_diffs.insert(new_atom_diff);
    }

    void apply(std::vector<T>& atom_chain) const
    {
        for(AtomDiff<T>* atom_diff: m_atom_diffs) {
            atom_diff->apply(atom_chain[atom_diff->get_id()]);
        }
    }
    void reverse(std::vector<T>& atom_chain) const
    {
        for(AtomDiff<T>* atom_diff: m_atom_diffs) {
            atom_diff->reverse(atom_chain[atom_diff->get_id()]);
        }
    }

private:
    std::set<AtomDiff<T>*> m_atom_diffs;
};

// one entry per frame
template<typename T>
using AtomDiffFrames = std::vector<AtomDiffFrame<T>>;

template<typename T>
class AtomChain {
public:
    T&       operator[](size_t idx) { return m_atoms[idx]; }
    const T& operator[](size_t idx) const { return m_atoms[idx]; }

    // final atom type -> change frame
    size_t size() { return m_atoms.size(); }
    void   add() { m_atoms.emplace_back(); }

    void set_frame(uint32_t frame, const AtomDiffFrames<T>& atom_diff_frames)
    {
        while(frame < m_frame)
            next_frame(atom_diff_frames);
        while(frame > m_frame)
            prev_frame(atom_diff_frames);
    }

private:
    void next_frame(const AtomDiffFrames<T>& atom_diff_frames)
    {
        MAKI_ASSERT_CRITICAL(m_frame + 1 < m_atoms.size(), "Current frame {} can't be increased.", m_frame);
        atom_diff_frames[m_frame + 1].apply(m_atoms);
        ++m_frame;
    }
    void prev_frame(const AtomDiffFrames<T>& atom_diff_frames)
    {
        MAKI_ASSERT_CRITICAL(m_frame - 1, "Current frame {} can't be decreased.", m_frame);
        atom_diff_frames[m_frame].reverse(m_atoms);
        --m_frame;
    }

private:
    uint32_t m_frame {0};
    // first frame stays empty
    std::vector<T> m_atoms {std::vector<T>(1)};
};

} // namespace Maki
