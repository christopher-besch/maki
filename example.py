#!/usr/bin/env python3

from build.maki.maki import init, RendererImplementation, RenderDriver


def main() -> None:
    init(RendererImplementation.opengl)
    render_driver = RenderDriver("Maki Python Test", 1280, 720)
    render_driver.run()
    del render_driver


if __name__ == "__main__":
    main()
