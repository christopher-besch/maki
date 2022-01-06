#include "pch.h"

#include "atom.h"

namespace Maki {

CuboidAtom& CuboidAtom::operator+=(const CuboidAtom& atom)
{
    add_pos(atom);
    add_col(atom);
    return *this;
}
CuboidAtom& CuboidAtom::operator-=(const CuboidAtom& atom)
{
    sub_pos(atom);
    sub_col(atom);
    return *this;
}
void CuboidAtom::add_pos(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] += atom.ver_pos[i];
    }
}
void CuboidAtom::add_col(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] += atom.ver_col[i];
    }
}
void CuboidAtom::sub_pos(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] -= atom.ver_pos[i];
    }
}
void CuboidAtom::sub_col(const CuboidAtom& atom)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] -= atom.ver_col[i];
    }
}

} // namespace Maki
