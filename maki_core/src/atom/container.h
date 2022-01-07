#pragma once

#include <set>
#include <vector>

#include "atom/atom.h"
#include "atom/atom_diff.h"
#include "core/log.h"

namespace Maki {

template<typename T>
class AtomChain;

// all changes required to convert frame into last or next
template<typename T>
class AtomDiffFrame {
public:
    AtomDiffFrame() = default;
    // copy not allowed
    AtomDiffFrame(const AtomDiffFrame<T>&) = delete;
    AtomDiffFrame& operator=(const AtomDiffFrame<T>&) = delete;
    AtomDiffFrame(AtomDiffFrame<T>&& other)
        : m_atom_diffs {std::move(other.m_atom_diffs)}
    {
        other.m_atom_diffs.clear();
    }
    AtomDiffFrame& operator=(AtomDiffFrame<T>&& other)
    {
        MAKI_LOG_WARN("destructing atom diff frame.");
        for(AtomDiff<T>* atom_diff: m_atom_diffs)
            delete atom_diff;
        m_atom_diffs = std::move(other.m_atom_diffs);
        other.m_atom_diffs.clear();
    }
    ~AtomDiffFrame()
    {
        MAKI_LOG_WARN("destructing atom diff frame (size {}).", m_atom_diffs.size());
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
    // sorted by id, then priority -> cache locality + correct order
    std::set<AtomDiff<T>*, CompareAtomDiff<T>> m_atom_diffs;
};

// represent entire runtime of scene
// one entry per frame
template<typename T>
class AtomDiffLifetime {
public:
    std::mutex& get_lock() const { return m_lock; }

    // low-level access only for read
    AtomDiffFrame<T>&       operator[](size_t idx) = delete;
    const AtomDiffFrame<T>& operator[](size_t idx) const
    {
        return m_atom_diff_frames[idx];
    }

    void ensure_frame_existence(uint32_t frame)
    {
        std::unique_lock<std::mutex> lock {m_lock};
        if(frame >= m_atom_diff_frames.size())
            m_atom_diff_frames.resize(frame + 1);
    }

    void add(uint32_t frame, AtomDiff<T>* diff)
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
    std::vector<AtomDiffFrame<T>> m_atom_diff_frames;
    // true -> render thread has to reload
    bool               m_invalidated {false};
    mutable std::mutex m_lock;
};

// representation of "current" frame
template<typename T>
class AtomChain {
public:
    T&       operator[](size_t idx) { return m_atoms[idx]; }
    const T& operator[](size_t idx) const { return m_atoms[idx]; }

    size_t   size() const { return m_atoms.size(); }
    uint32_t add()
    {
        std::unique_lock<std::mutex> lock {m_lock};
        m_atoms.emplace_back();
        return m_atoms.size() - 1;
    }

    void set_frame(uint32_t frame, const AtomDiffLifetime<T>& atom_diff_lifetime)
    {
        std::unique_lock<std::mutex> lock {m_lock};
        std::unique_lock<std::mutex> atom_diff_lifetime_lock {atom_diff_lifetime.get_lock()};
        while(frame < m_frame)
            next_frame(atom_diff_lifetime);
        while(frame > m_frame)
            prev_frame(atom_diff_lifetime);
    }

private:
    void next_frame(const AtomDiffLifetime<T>& atom_diff_lifetime)
    {
        MAKI_ASSERT_CRITICAL(m_frame + 1 < m_atoms.size(), "Current frame {} can't be increased.", m_frame);
        atom_diff_lifetime[m_frame + 1].apply(m_atoms);
        ++m_frame;
    }
    void prev_frame(const AtomDiffLifetime<T>& atom_diff_lifetime)
    {
        MAKI_ASSERT_CRITICAL(m_frame - 1, "Current frame {} can't be decreased.", m_frame);
        atom_diff_lifetime[m_frame].reverse(m_atoms);
        --m_frame;
    }

private:
    uint32_t m_frame {0};
    // first frame stays empty
    std::vector<T>     m_atoms {};
    mutable std::mutex m_lock;
};

} // namespace Maki
