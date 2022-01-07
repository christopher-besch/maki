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

    constexpr float space {4.0f};
    for(float x {0.0f}; x < 30.0f * space; x += space) {
        for(float y {0.0f}; y < 30.0f * space; y += space) {
            for(float z {0.0f}; z < 2.0f * space; z += space) {
                uint32_t cuboid = render_driver->add_cuboid_atom();
                render_driver->render_cuboid_atom(cuboid, 1, true);
                render_driver->translate_cuboid_atom(cuboid, 1, {x, y, z});
                render_driver->color_cuboid_atom(cuboid, 2, {0.8f, 0.8f, 0.0f, 0.5f});
            }
        }
    }
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
