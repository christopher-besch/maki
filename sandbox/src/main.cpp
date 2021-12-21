#include "maki.h"

int main()
{
    Maki::RenderDriver* render_driver = Maki::init(Maki::Renderer::Implementation::opengl, "Maki Test", 920, 1280);
    MAKI_CLIENT_LOG_EXTRA("After Render Loop");
    Maki::shutdown(render_driver);
}
