#include "maki.h"

int main()
{
    Maki::Renderer* renderer = Maki::init(Maki::Renderer::Implementation::open_gl);
    MAKI_CLIENT_LOG_EXTRA("Hello World");
    Maki::shutdown(renderer);
}
