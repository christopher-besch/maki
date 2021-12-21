#include "maki.h"

int main()
{
    Maki::Renderer* renderer = Maki::init(Maki::Renderer::Implementation::open_gl, "Maki Test", 920, 1280);
    MAKI_CLIENT_LOG_EXTRA("Hello World");
    while(1) {
    }
    Maki::shutdown(renderer);
}
