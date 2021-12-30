# Maki

**M**athematical **A**nimation and **K**nickknack **I**nscriber (Maki), an experimental rendering backend for [Manim](https://github.com/ManimCommunity/manim). 

This is a cross-platform project. But right now only Linux has been tested.
If you know what you're doing, this will run everywhere.

## Requirements

### Debian/Ubuntu

```
sudo apt install build-essential cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libglew-dev
```

## Compilation

```
git clone https://github.com/christopher-besch/maki --recurse
cd maki
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Dplatform=glfw
cmake --build . -j4
```

## Run

Either from C++
```
./build/sandbox/sandbox
```

or from Python.
```
./example.py
```

## References
- [Light3039/Light](https://github.com/Light3039/Light)
- [christopher-besch/opengl_reference](https://github.com/christopher-besch/opengl_reference)
- [christopher-besch/lynton_legacy](https://github.com/christopher-besch/lynton_legacy)
- [christopher-besch/lynton](https://github.com/christopher-besch/lynton)
- [christopher-besch/ray_tracer](https://github.com/christopher-besch/ray_tracer)
- [The Cherno OpenGL](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [opengl-tutorial.org](http://www.opengl-tutorial.org)

