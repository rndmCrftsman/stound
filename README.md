# stound
Stounding, right?

# Prerequisites
- Ninja
- GCC
- CMake
- Libraries provided through Conan 1.61.0:
  - Imgui 1.89.9-docking
  - GLFW 3.3.8
  - GLEW 2.2.0
  - miniaudio 0.11.17

# Build steps:
```
mkdir build && cd build
conan install .. --build=missing
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

