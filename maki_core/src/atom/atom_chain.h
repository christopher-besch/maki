#pragma once

#include "atom/atom_diff_lifetime.h"

namespace Maki {

// representation of "current" frame
template<typename AtomType>
class AtomChain {
public:
    AtomType&       operator[](size_t idx) { return m_atoms[idx]; }
    const AtomType& operator[](size_t idx) const { return m_atoms[idx]; }

    size_t   size() const { return m_atoms.size(); }
    uint32_t add()
    {
        std::unique_lock<std::mutex> lock {m_lock};
        m_atoms.emplace_back();
        return m_atoms.size() - 1;
    }

    void set_frame(uint32_t frame, const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        std::unique_lock<std::mutex> lock {m_lock};
        std::unique_lock<std::mutex> atom_diff_lifetime_lock {atom_diff_lifetime.get_lock()};
        while(frame < m_frame)
            next_frame(atom_diff_lifetime);
        while(frame > m_frame)
            prev_frame(atom_diff_lifetime);
    }

private:
    void next_frame(const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        MAKI_ASSERT_CRITICAL(m_frame + 1 < m_atoms.size(), "Current frame {} can't be increased.", m_frame);
        atom_diff_lifetime[m_frame + 1].apply(m_atoms);
        ++m_frame;
    }
    void prev_frame(const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        MAKI_ASSERT_CRITICAL(m_frame - 1, "Current frame {} can't be decreased.", m_frame);
        atom_diff_lifetime[m_frame].reverse(m_atoms);
        --m_frame;
    }

private:
    uint32_t m_frame {0};
    // first frame stays empty
    std::vector<AtomType> m_atoms {};
    mutable std::mutex    m_lock;
};

} // namespace Maki
