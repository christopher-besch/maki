#include "maki.h"

int main()
{
    Maki::init(Maki::Renderer::Implementation::opengl);
    Maki::RenderDriver* render_driver  = new Maki::RenderDriver("Maki Test", 1280, 720);
    Maki::RenderDriver* render_driver2 = new Maki::RenderDriver("Maki Test2", 1280, 720);
    MAKI_CLIENT_LOG_EXTRA("Before Render Loop");
    render_driver->await_termination();
    render_driver2->await_termination();
    MAKI_CLIENT_LOG_EXTRA("After Render Loop");
    delete render_driver;
    delete render_driver2;
}
