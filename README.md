# Maki

**M**athematical **A**nimation and **K**nickknack **I**nscriber (Maki), an experimental rendering backend for [Manim](https://github.com/ManimCommunity/manim). 

## References

- [christopher-besch/opengl_reference](https://github.com/christopher-besch/opengl_reference)
- [christopher-besch/lynton_legacy](https://github.com/christopher-besch/lynton_legacy)
- [christopher-besch/lynton](https://github.com/christopher-besch/lynton)
- [christopher-besch/ray_tracer](https://github.com/christopher-besch/ray_tracer)
- [The Cherno OpenGL](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [opengl-tutorial.org](http://www.opengl-tutorial.org)

## Compilation

```
git clone https://github.com/christopher-besch/opengl_test --recurse
cd opengl_test
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build . -j4
```
