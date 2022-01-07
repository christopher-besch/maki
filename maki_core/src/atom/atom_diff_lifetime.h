#pragma once

#include <vector>

#include "atom/atom_diff_frame.h"

namespace Maki {

// represent entire runtime of scene
// one entry per frame
template<typename AtomType>
class AtomDiffLifetime {
public:
    std::mutex& get_lock() const { return m_lock; }

    // low-level access only for read
    AtomDiffFrame<AtomType>&       operator[](size_t idx) = delete;
    const AtomDiffFrame<AtomType>& operator[](size_t idx) const
    {
        return m_atom_diff_frames[idx];
    }

    void ensure_frame_existence(uint32_t frame)
    {
        std::unique_lock<std::mutex> lock {m_lock};
        if(frame >= m_atom_diff_frames.size())
            m_atom_diff_frames.resize(frame + 1);
    }

    void add(uint32_t frame, AtomDiff<AtomType>* diff)
    {
        std::unique_lock<std::mutex> lock {m_lock};
        MAKI_ASSERT_CRITICAL(frame < m_atom_diff_frames.size(), "Frame {} hasn't been created yet for atom diff lifetime with {} frames.", frame, m_atom_diff_frames.size());
        m_atom_diff_frames[frame].add(diff);
        m_invalidated = true;
    }
    void validate()
    {
        std::unique_lock<std::mutex> lock {m_lock};
        m_invalidated = false;
    }

private:
    std::vector<AtomDiffFrame<AtomType>> m_atom_diff_frames;
    // true -> render thread has to reload
    bool               m_invalidated {false};
    mutable std::mutex m_lock;
};

} // namespace Maki
