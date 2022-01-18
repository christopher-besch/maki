# Maki

**M**athematical **A**nimation and **K**nickknack **I**nscriber (Maki), an experimental rendering backend for [Manim](https://github.com/ManimCommunity/manim).
Or: **How to Teach Manim Time Travel.**

![image](https://user-images.githubusercontent.com/57909184/148649899-0a890deb-c435-493e-8a89-419e895296dd.png)

This is a cross-platform project.
But right now only Linux-builds have been tested.
Though if you know what you're doing, this will compile and run everywhere.

At the moment this project is under development, thus the documentation and volume of comments is left to be desired.

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
cmake .. -DCMAKE_BUILD_TYPE=Debug -Dplatform=glfw
cmake --build . -j4
```

## Use

You can take a look at `maki_showcase.ipynb`.
It contains a few examples for Maki.
For it to function correctly you have to copy (or symlink) the compiled shared object for Python (for example `maki.cpython-310-x86_64-linux-gnu.so`) into the root of this project.
You can find that shared object in `build/maki` (if you called your build directory that).

The examples work with both Debug and Release builds, but some are excruciatingly slow in the former.
Please try both modes before reporting any bugs or performance problems.

On a related note:
Please do inform the author of any problems, bugs or feature requests.
You can use the [issues](https://github.com/christopher-besch/maki/issues) for that.

## References

- [opengl_reference](https://github.com/christopher-besch/opengl_reference)
- [lynton_legacy](https://github.com/christopher-besch/lynton_legacy)
- [lynton](https://github.com/christopher-besch/lynton)
- [ray_tracer](https://github.com/christopher-besch/ray_tracer)
- [Light](https://github.com/Light3039/Light)
- [The Cherno OpenGL](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [opengl-tutorial.org](http://www.opengl-tutorial.org)
- [imgui-cmake](https://github.com/Pesc0/imgui-cmake)
- [marshalling glm types](https://github.com/pybind/pybind11/issues/430)
- [morphing in Blender](https://www.youtube.com/watch?v=SgDhzkv-p6s)
- [morphing in babylon.js](https://doc.babylonjs.com/divingDeeper/mesh/dynamicMeshMorph)
