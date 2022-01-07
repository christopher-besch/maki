#pragma once

#include <vector>

#include "atom/atom_diff_frame.h"
#include "core/definitions.h"

namespace Maki {

// represent entire runtime of scene
template<typename AtomType>
class AtomDiffLifetime {
public:
    size_t size() const
    {
        rec_lock lock {m_mutex};
        return m_atom_diff_frames.size();
    }

    void ensure_frame_existence(uint32_t frame)
    {
        rec_lock lock {m_mutex};
        if(frame >= m_atom_diff_frames.size())
            m_atom_diff_frames.resize(frame + 1);
    }

    void add(uint32_t frame, AtomDiff<AtomType>* diff)
    {
        rec_lock lock {m_mutex};
        MAKI_ASSERT_CRITICAL(frame < m_atom_diff_frames.size(), "Frame {} hasn't been created yet for atom diff lifetime with {} frames.", frame, m_atom_diff_frames.size());
        m_atom_diff_frames[frame].add(diff);
        m_first_outdated_frame = frame;
    }
    uint32_t get_first_outdated_frame()
    {
        rec_lock lock {m_mutex};
        return m_first_outdated_frame;
    }
    void updated()
    {
        rec_lock lock {m_mutex};
        m_first_outdated_frame = m_atom_diff_frames.size();
    }

    void apply(uint32_t frame, std::vector<AtomType>& atoms) const
    {
        rec_lock lock {m_mutex};
        m_atom_diff_frames[frame].apply(atoms);
    }
    void reverse(uint32_t frame, std::vector<AtomType>& atoms) const
    {
        rec_lock lock {m_mutex};
        m_atom_diff_frames[frame].reverse(atoms);
    }

private:
    // one entry per frame
    // first frame stays empty
    std::vector<AtomDiffFrame<AtomType>> m_atom_diff_frames {std::vector<AtomDiffFrame<AtomType>>(1)};
    // render thread has to reload when it's atom chain is at or after first outdated frame
    uint32_t          m_first_outdated_frame {1};
    mutable rec_mutex m_mutex;
};

} // namespace Maki
