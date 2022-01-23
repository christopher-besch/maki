#include "maki.h"

int main()
{
    Maki::init(Maki::Renderer::Implementation::opengl);
    Maki::RenderDriver* render_driver = new Maki::RenderDriver("Maki Test", 1280, 720);
    MAKI_CLIENT_LOG_EXTRA("Before Render Loop");
    // uint32_t cuboid = render_driver->add_cuboid_atom();
    // render_driver->render_cuboid_atom(cuboid, 3, true);
    // render_driver->translate_cuboid_atom(cuboid, 4, {1.0f, 1.0f, 1.0f});
    // render_driver->render_cuboid_atom(cuboid, 5, false);
    // render_driver->render_cuboid_atom(cuboid, 10, true);

#if 0
    constexpr float space {4.0f};
    uint32_t        frame {1};
    for(float x {0.0f}; x < 50.0f * space; x += space) {
        for(float y {0.0f}; y < 50.0f * space; y += space) {
            for(float z {0.0f}; z < 50.0f * space; z += space) {
                uint32_t cuboid = render_driver->add_atom<Maki::CuboidAtom>();
                render_driver->show_atom<Maki::CuboidAtom>(cuboid, frame, true);
                render_driver->translate_atom<Maki::CuboidAtom>(cuboid, frame, {x, y, z});
                render_driver->color_atom<Maki::CuboidAtom>(cuboid, frame, {0.8f, 0.8f, 0.0f, 0.1f});
                // for(uint32_t anim_frame {101}; anim_frame < 200; ++anim_frame)
                //     render_driver->translate_cuboid_atom(cuboid, anim_frame, {0.2f, 0.0f, 0.0f});
                ++frame;
                // MAKI_CLIENT_LOG_EXTRA("new cube {} {} {}", x, y, z);
            }
        }
    }
#endif
#if 1
    uint32_t cuboid = render_driver->add_atom<Maki::CuboidAtom>();
    render_driver->show_atom<Maki::CuboidAtom>(cuboid, 1, true);

    // uint32_t cuboid2 = render_driver->add_atom<Maki::CuboidAtom>();
    // render_driver->show_atom<Maki::CuboidAtom>(cuboid2, 1, true);
    // render_driver->translate_atom<Maki::CuboidAtom>(cuboid2, 1, {0.0f, 0.0f, 1.0f});
    // render_driver->color_atom<Maki::CuboidAtom>(cuboid2, 1, {1.0f, 1.0f, 0.0f, 1.0f});

    uint32_t rect = render_driver->add_atom<Maki::QuadrilateralAtom>();
    render_driver->show_atom<Maki::QuadrilateralAtom>(rect, 2, true);
    render_driver->translate_atom<Maki::QuadrilateralAtom>(rect, 2, {3.0f, 3.0f, 0.0f});
#endif
    MAKI_CLIENT_LOG_EXTRA("done creating");
    // uint32_t cuboid = render_driver->add_cuboid_atom();
    // render_driver->render_cuboid_atom(cuboid, 1, true);
    // render_driver->translate_cuboid_atom(cuboid, 1, {1, 1, 1});
    // uint32_t cuboid1 = render_driver->add_cuboid_atom();
    // render_driver->render_cuboid_atom(cuboid1, 2, true);
    // render_driver->translate_cuboid_atom(cuboid1, 2, {2, 2, 2});

    // render_driver->color_cuboid_atom(cuboid, 11, {1.0f, 1.0f, 0.0f, 1.0f});
    render_driver->await_termination();
    MAKI_CLIENT_LOG_EXTRA("After Render Loop");
    delete render_driver;
}
