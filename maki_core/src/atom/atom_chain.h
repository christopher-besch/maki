#pragma once

#include "atom/atom_diff_lifetime.h"
#include "core/definitions.h"

namespace Maki {

// representation of current frame
template<typename AtomType>
class AtomChain {
public:
    AtomType&       operator[](size_t idx) { return m_atoms[idx]; }
    const AtomType& operator[](size_t idx) const { return m_atoms[idx]; }

    size_t size() const
    {
        rec_lock lock {m_lock};
        return m_atoms.size();
    }
    uint32_t add()
    {
        rec_lock lock {m_lock};
        m_atoms.emplace_back();
        return m_atoms.size() - 1;
    }

    void set_frame(uint32_t frame, const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        rec_lock lock {m_lock};
        rec_lock atom_diff_lifetime_lock {atom_diff_lifetime.get_lock()};
        MAKI_ASSERT_CRITICAL(atom_diff_lifetime.size() > frame, "Frame {} hasn't been created yet.", frame);
        while(m_frame < frame)
            next_frame(atom_diff_lifetime);
        while(m_frame > frame)
            prev_frame(atom_diff_lifetime);
    }

private:
    void next_frame(const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        atom_diff_lifetime.apply(m_frame + 1, m_atoms);
        ++m_frame;
    }
    void prev_frame(const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        atom_diff_lifetime.reverse(m_frame, m_atoms);
        --m_frame;
    }

private:
    // frame that has been applied last
    uint32_t              m_frame {0};
    std::vector<AtomType> m_atoms {};
    mutable rec_mutex     m_lock;
};

} // namespace Maki
