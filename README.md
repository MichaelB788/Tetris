# Table of Contents

1. [Tetris](#tetris)

2. [Dependencies](#dependencies)
	 - [Windows Dependencies](#windows-dependencies)
	 - [Linux Dependencies](#linux-dependencies)

3. [License](#license)

# Tetris

A simple game of Tetris implemented using C++ and SDL2. It is designed to be a fun and educational project for myself and others who want to learn
more about game development, C++, and high-level graphics rendering. The game is compatible with both Linux and Windows operating systems, using
CMake for building the project and vcpkg for managing dependencies.

# Dependencies

Before you can build and run the Tetris game, you need to install the following dependencies:

### Windows Dependencies 

- Visual Studio 2019 or later (with C++ development tools)
	-	See [Visual Studio Downloads](https://visualstudio.microsoft.com/downloads/) for instructions on how to install Visual Studio. 
- vcpkg (for managing dependencies)
	- See [vcpkg GitHub Repository](https://github.com/microsoft/vcpkg)

### Linux Dependencies

- GCC or Clang (C++ compiler)
- CMake (for building the project)
- SDL2 (Simple DirectMedia Layer 2)
- SDL2_ttf (for loading fonts)

**You can install these dependencies using your package manager**. For example, on Ubuntu or Debian-based systems, you can run:
	```bash
	sudo apt install build-essential cmake libsdl2-dev libsdl2-ttf-dev
	```
For more information on how to install SDL2 and SDL2_ttf, refer to the [SDL2 Wiki](https://wiki.libsdl.org/Installation).

> Note: Though not required on Linux, vcpkg can also be installed and used. However, it might just be easier and faster to use your Linux package manager.

### Building and Running the Game

This project is not yet ready for building and running. Instructions will be added in the future.

# License

This project is open source and distributed under the MIT License.
