# OpenGL Test

Based on [opengl-tutorial.org](http://www.opengl-tutorial.org).

## Compilation

```
git clone https://github.com/christopher-besch/opengl_test --recurse
cd opengl_test
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Dplatform=glfw
cmake --build . -j4
```
