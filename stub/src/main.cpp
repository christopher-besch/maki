#include "maki.h"

int main()
{
    Maki::init(Maki::Renderer::Implementation::opengl);
    Maki::RenderDriver* render_driver = new Maki::RenderDriver("Maki Test", 1280, 720);
    MAKI_CLIENT_LOG_EXTRA("Before Render Loop");
    uint32_t cuboid = render_driver->add_cuboid_atom();
    render_driver->render_cuboid_atom(cuboid, 3, true);
    render_driver->translate_cuboid_atom(cuboid, 4, {1.0f, 1.0f, 1.0f});
    render_driver->render_cuboid_atom(cuboid, 5, false);
    render_driver->render_cuboid_atom(cuboid, 10, true);
    render_driver->color_cuboid_atom(cuboid, 11, {1.0f, 1.0f, 0.0f, 1.0f});
    int x;
    while(1) {
        std::cin >> x;
        if(x == -1) {
            render_driver->render_cuboid_atom(cuboid, 5, true);
            continue;
        }
        if(x == -2) {
            break;
        }
        render_driver->set_frame(x);
        std::cout << "frame: " << x << std::endl;
    }
    render_driver->await_termination();
    MAKI_CLIENT_LOG_EXTRA("After Render Loop");
    delete render_driver;
}
