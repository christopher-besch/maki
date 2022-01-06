#include "pch.h"

#include "atom.h"

namespace Maki {

// TODO: should maybe reside in atom_diff
CuboidAtom& CuboidAtom::operator+=(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] += atom.ver_pos[i];
        ver_col[i] += atom.ver_col[i];
    }
    return *this;
}
CuboidAtom& CuboidAtom::operator-=(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] -= atom.ver_pos[i];
        ver_col[i] -= atom.ver_col[i];
    }
    return *this;
}
// void CuboidAtom::add_pos(const CuboidAtom& atom)
// {
//     for(size_t i {0}; i != ver_pos.size(); ++i) {
//         ver_pos[i] += atom.ver_pos[i];
//     }
// }
// void CuboidAtom::add_col(const CuboidAtom& atom)
// {
//     for(size_t i {0}; i != ver_col.size(); ++i) {
//         ver_col[i] += atom.ver_col[i];
//     }
// }
// void CuboidAtom::sub_pos(const CuboidAtom& atom)
// {
//     for(size_t i {0}; i != ver_pos.size(); ++i) {
//         ver_pos[i] -= atom.ver_pos[i];
//     }
// }
// void CuboidAtom::sub_col(const CuboidAtom& atom)
// {
//     for(size_t i {0}; i != ver_col.size(); ++i) {
//         ver_col[i] -= atom.ver_col[i];
//     }
// }
} // namespace Maki
