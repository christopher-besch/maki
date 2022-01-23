#include "pch.h"

#include "cuboid_atom.h"

namespace Maki {

// TODO: remove code duplication
CuboidAtom& CuboidAtom::operator+=(const CuboidAtom& atom)
{
    add_pos(atom.ver_pos);
    add_col(atom.ver_col);
    return *this;
}
CuboidAtom& CuboidAtom::operator-=(const CuboidAtom& atom)
{
    sub_pos(atom.ver_pos);
    sub_col(atom.ver_col);
    return *this;
}
void CuboidAtom::add_pos(const std::array<vec3, 8>& delta_pos)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] += delta_pos[i];
    }
}
void CuboidAtom::sub_pos(const std::array<vec3, 8>& delta_pos)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] -= delta_pos[i];
    }
}
void CuboidAtom::add_col(const std::array<vec4, 8>& delta_col)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] += delta_col[i];
    }
}
void CuboidAtom::sub_col(const std::array<vec4, 8>& delta_col)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] -= delta_col[i];
    }
}

} // namespace Maki
