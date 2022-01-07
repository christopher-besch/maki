#pragma once

#include "atom/atom_diff_lifetime.h"
#include "core/definitions.h"

namespace Maki {

// representation of current frame
template<typename AtomType>
class AtomChain {
public:
    AtomType& operator[](size_t idx)
    {
        lock lock {m_atoms_mutex};
        return m_atoms[idx];
    }
    const AtomType& operator[](size_t idx) const
    {
        lock lock {m_atoms_mutex};
        return m_atoms[idx];
    }

    uint32_t get_frame() { return m_frame; }
    size_t   size() const
    {
        lock lock {m_atoms_mutex};
        return m_atoms.size();
    }
    uint32_t add()
    {
        lock lock {m_atoms_mutex};
        m_atoms.emplace_back();
        return m_atoms.size() - 1;
    }

    void set_frame(uint32_t frame, const AtomDiffLifetime<AtomType>& atom_diff_lifetime)
    {
        lock lock {m_atoms_mutex};
        MAKI_ASSERT_CRITICAL(atom_diff_lifetime.size() > frame, "Frame {} hasn't been created yet.", frame);
        while(m_frame < frame)
            next_frame(atom_diff_lifetime);
        while(m_frame > frame)
            prev_frame(atom_diff_lifetime);
    }
    void chrono_sync()
    {
        lock lock {m_atoms_mutex};
        MAKI_LOG_EXTRA("Chrono Sync initiated.");
        // safe current state
        size_t target_atom_count = m_atoms.size();

        // evict data
        m_atoms.resize(0);
        m_frame = 0;

        // sync
        m_atoms.resize(target_atom_count);
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
    mutable mutex         m_atoms_mutex;
};

} // namespace Maki
