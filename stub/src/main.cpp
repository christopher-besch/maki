#include "maki.h"

int main()
{
    Maki::init(Maki::Renderer::Implementation::opengl);
    Maki::RenderDriver* render_driver = new Maki::RenderDriver("Maki Test", 1280, 720);
    MAKI_CLIENT_LOG_EXTRA("Before Render Loop");
    uint32_t cuboid = render_driver->add_cuboid_atom();
    render_driver->render_cuboid_atom(cuboid, 3, true);
    render_driver->render_cuboid_atom(cuboid, 4, true);
    render_driver->render_cuboid_atom(cuboid, 5, false);
    render_driver->await_termination();
    MAKI_CLIENT_LOG_EXTRA("After Render Loop");
    delete render_driver;
}
