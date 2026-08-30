# Tetris

Tetris, written in C++. Much of the project uses the SDL3 framework for window
creation, rendering, input handling.

# Requirements

The following are the minimum requirements to run the project:

- A C/C++ compiler (such as GCC or MSVC) that supports C++23
- CMake (with at least version 3.20)
- A C/C++ generator, such as Ninja or Makefile.
- SDL3, SDL3_TTF, and SDL3_IMG development files

# Build Instructions

## Linux

If you just want to try the program, build the project in `Release` mode:

```bash
cmake -B build -S .\
    -DCMAKE_BUILD_TYPE=Release\
    -G Ninja # This line may be omitted if using Make
```

Otherwise, build the project in `Debug` mode:

```bash
cmake -B build -S .\
    -DCMAKE_EXPORT_COMPILE_COMMANDS=YES\
    -DCMAKE_BUILD_TYPE=Debug\
    -G Ninja # This line may be omitted if using Make
```

You can then build or rebuild the project using:

```bash
cmake --build build
```

The resulting binary can be found under `build/Release/` or `build/Debug/`,
depending on the build type.

# License

MIT
