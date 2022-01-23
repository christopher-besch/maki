#pragma once

#include <vector>

#include "atom/atom_diff_frame.h"
#include "core/definitions.h"
#include "core/thread_safety.h"

namespace Maki {

// represent entire runtime of scene
template<typename AtomType>
class AtomDiffLifetime {
public:
    // to be run from control thread //

    void ensure_frame_existence(uint32_t frame)
    {
        ASSERT_CONTROL_THREAD();
        rec_lock lock {m_mutex};
        if(frame >= m_atom_diff_frames.size())
            m_atom_diff_frames.resize(frame + 1);
    }

    void add(uint32_t frame, const AtomDiff<AtomType>* diff)
    {
        ASSERT_CONTROL_THREAD();
        rec_lock lock {m_mutex};
        MAKI_ASSERT_CRITICAL(frame < m_atom_diff_frames.size(), "Frame {} hasn't been created yet for atom diff lifetime with {} frames.", frame, m_atom_diff_frames.size());
        m_atom_diff_frames[frame].add(diff);
        m_first_outdated_frame = frame;
    }

    // to be run from render thread //

    bool is_outdated(uint32_t frame)
    {
        ASSERT_RENDER_THREAD();
        rec_lock lock {m_mutex};
        if(frame >= m_first_outdated_frame)
            return true;
        // not outdated
        update();
        return false;
    }
    void update()
    {
        ASSERT_RENDER_THREAD();
        rec_lock lock {m_mutex};
        m_first_outdated_frame = m_atom_diff_frames.size();
    }

    // can be run from either thread //

    size_t size() const
    {
        rec_lock lock {m_mutex};
        return m_atom_diff_frames.size();
    }

    // apply changes of requested frame to all atoms of an atom chain
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
    uint32_t m_first_outdated_frame {1};
    // lock m_atom_diff_frames and m_first_outdated_frame
    mutable rec_mutex m_mutex;
};

} // namespace Maki
