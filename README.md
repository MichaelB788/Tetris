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
	- You can install GCC or Clang using your package manager. For example, on Ubuntu, you can run:
		```bash
		sudo apt install build-essential
		```

- CMake (for building the project)
	- You can install CMake using your package manager. For example, on Ubuntu, you can run:
		```bash
		sudo apt install cmake
		```

- SDL2 (Simple DirectMedia Layer 2)
	- You can install SDL2 using your package manager. For example, on Ubuntu, you can run:
		```bash
		sudo apt install libsdl2-dev
		```

- vcpkg (for managing dependencies)
	- See [vcpkg GitHub Repository](https://github.com/microsoft/vcpkg)

# License

This project is open source and distributed under the MIT License.
