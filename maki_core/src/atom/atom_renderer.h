#pragma once

#include "atom/renderers/cuboid_renderer.h"
#include "atom/renderers/quadrilateral_renderer.h"

namespace Maki {

// used as an interface between OOP implementation of renderer and AtomDispenser using generic programming
// can be used like:
// AtomRendererRouter<CuboidAtom>::type* m_cuboid_renderer;
template<typename AtomType>
struct AtomRendererRouter {
    // can't be used unspecialized
    typedef void type;
};

template<>
struct AtomRendererRouter<CuboidAtom> {
    typedef CuboidRenderer type;
};

template<>
struct AtomRendererRouter<QuadrilateralAtom> {
    typedef QuadrilateralRenderer type;
};

} // namespace Maki
