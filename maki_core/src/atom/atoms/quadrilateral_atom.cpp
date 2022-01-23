#include "pch.h"

#include "quadrilateral_atom.h"

namespace Maki {

// TODO: remove code duplication
QuadrilateralAtom& QuadrilateralAtom::operator+=(const QuadrilateralAtom& atom)
{
    add_pos(atom.ver_pos);
    add_col(atom.ver_col);
    return *this;
}
QuadrilateralAtom& QuadrilateralAtom::operator-=(const QuadrilateralAtom& atom)
{
    sub_pos(atom.ver_pos);
    sub_col(atom.ver_col);
    return *this;
}
void QuadrilateralAtom::add_pos(const std::array<vec3, 4>& delta_pos)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] += delta_pos[i];
    }
}
void QuadrilateralAtom::sub_pos(const std::array<vec3, 4>& delta_pos)
{
    for(size_t i {0}; i != ver_pos.size(); ++i) {
        ver_pos[i] -= delta_pos[i];
    }
}
void QuadrilateralAtom::add_col(const std::array<vec4, 4>& delta_col)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] += delta_col[i];
    }
}
void QuadrilateralAtom::sub_col(const std::array<vec4, 4>& delta_col)
{
    for(size_t i {0}; i != ver_col.size(); ++i) {
        ver_col[i] -= delta_col[i];
    }
}

} // namespace Maki
