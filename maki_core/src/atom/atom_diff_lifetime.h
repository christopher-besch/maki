#pragma once

#include <vector>

#include "atom/atom_diff_frame.h"
#include "core/definitions.h"

namespace Maki {

// represent entire runtime of scene
template<typename AtomType>
class AtomDiffLifetime {
public:
    rec_mutex& get_lock() const { return m_lock; }

    size_t size() const
    {
        rec_lock lock {m_lock};
        return m_atom_diff_frames.size();
    }

    void ensure_frame_existence(uint32_t frame)
    {
        rec_lock lock {m_lock};
        if(frame >= m_atom_diff_frames.size())
            m_atom_diff_frames.resize(frame + 1);
    }

    void add(uint32_t frame, AtomDiff<AtomType>* diff)
    {
        rec_lock lock {m_lock};
        MAKI_ASSERT_CRITICAL(frame < m_atom_diff_frames.size(), "Frame {} hasn't been created yet for atom diff lifetime with {} frames.", frame, m_atom_diff_frames.size());
        m_atom_diff_frames[frame].add(diff);
        m_invalidated = true;
    }
    void validate()
    {
        rec_lock lock {m_lock};
        m_invalidated = false;
    }

    void apply(uint32_t frame, std::vector<AtomType>& atoms) const
    {
        m_atom_diff_frames[frame].apply(atoms);
    }
    void reverse(uint32_t frame, std::vector<AtomType>& atoms) const
    {
        m_atom_diff_frames[frame].reverse(atoms);
    }

private:
    // one entry per frame
    // first frame stays empty
    std::vector<AtomDiffFrame<AtomType>> m_atom_diff_frames {std::vector<AtomDiffFrame<AtomType>>(1)};
    // true -> render thread has to reload
    bool              m_invalidated {false};
    mutable rec_mutex m_lock;
};

} // namespace Maki
