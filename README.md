# Tetris

Tetris clone written in C++, using the SDL3 rendering library.

![image](assets/readme_img/tetris_preview.png)

# Controls

- Step Left: A
- Step Right: D
- Soft Drop: S
- Hard Drop: W
- Clockwise Rotation: Right Arrow
- Counterclockwise Rotation: Left Arrow
- Hold Piece: Up Arrow

# Requirements

- vcpkg (for installing SDL3 dependencies)
- GCC (Linux), MSVC (Windows), or Clang (MacOS)
- CMake
- Ninja

# Build Instructions

Build the project in `Release` mode to try it out:

```bash
cmake --preset Release
```

Build the project in `Debug` mode for testing/development:

```bash
cmake --preset Debug
```

You can then (re)build the project using:

```bash
cmake --build build
```

The program binary will be generated under `build/Release/` or `build/Debug/`,
depending on the build type.

# License

MIT
