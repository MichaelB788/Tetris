# Table of Contents

- [Table of Contents](#table-of-contents)
- [Tetris](#tetris)
- [Dependencies](#dependencies)
    - [Windows Dependencies](#windows-dependencies)
    - [Linux Dependencies](#linux-dependencies)
- [Building](#building)
    - [Building on Windows](#building-on-windows)
      - [Build the Project with Visual Studio (recommended)](#build-the-project-with-visual-studio-recommended)
      - [Build the Project with Windows Terminal](#build-the-project-with-windows-terminal)
    - [Building on Linux](#building-on-linux)
- [Running Unit Tests](#running-unit-tests)
- [License](#license)

# Tetris

A simple game of Tetris implemented using C++ and SDL2. It is designed to be a fun and educational project for myself and others who want to learn
more about game development, C++, and high-level graphics rendering. The game is compatible with both Linux and Windows operating systems, using
CMake for building the project and vcpkg for managing dependencies.

# Dependencies

Before you can build and run the Tetris game, you need to install the following dependencies:

### Windows Dependencies 

- Git (for version control and cloning the repo)
	- See [git Downloads](https://git-scm.com/downloads)
- Visual Studio 2019 or later (**HIGHLY RECOMMENDED** for C++ development tools)
	-	See [Visual Studio Downloads](https://visualstudio.microsoft.com/downloads/) 
- vcpkg (for managing dependencies)
	- See [vcpkg GitHub Repository](https://github.com/microsoft/vcpkg)

### Linux Dependencies

- git (for version control and cloning the repo)
- GCC or Clang (C++ compiler)
- CMake (for building the project)
- SDL2 (Simple DirectMedia Layer 2)
- SDL2_ttf (for loading fonts)

**You can install these dependencies using your package manager**. For example, on Ubuntu or Debian-based systems, you can run:

```bash
sudo apt install git build-essential cmake libsdl2-dev libsdl2-ttf-dev
```

**You may also install Catch2 manually**, however it is not mandatory as the CMake file under `extern/` should fetch a working version of Catch2 if
it isn't already found during the configure step (i.e, when running `cmake ..`).

> Note: Though not required on Linux, vcpkg can also be installed and used. However, it might just be easier and faster to use your Linux package manager.

# Building

Before getting into the platform specific steps, you need to clone the project files into your system by **cloning this repository with git**.

Go into a directory you wish to install the project files in and copy and paste the following commands in your terminal of choice (Powershell, Command Prompt, etc.):

```powershell
git clone https://github.com/MichaelB788/Tetris.git
cd Tetris
```

### Building on Windows

Building the project on Windows should be straightforward, as **vcpkg handles all the necessary dependencies for the project**.

First, in the root of the `Tetris` directory, create a file named `CMakeUserPresets.json` and copy and paste the following:

```json
{
  "version": 3,
  "configurePresets": [
    // Debug mode
    {
      "name": "default-debug",
      "inherits": "vcpkg-debug",
      "environment": {
        "VCPKG_ROOT": "<path-to-vcpkg>"
      }
    },
    // Release mode
    {
      "name": "default-release",
      "inherits": "vcpkg-release",
      "environment": {
        "VCPKG_ROOT": "<path-to-vcpkg>"
      }
    }
  ]
}
```

**Replace `<path-to-vcpkg>` with the absolute path of vcpkg.** For example if you decided to install vcpkg in `C:\Program Files\`, then `<path-to-vcpkg>` may look like this:

```
C:/Program Files/vcpkg
```

#### Build the Project with Visual Studio (recommended)

If you use Visual Studio, there should be a [configuration dropdown](https://learn.microsoft.com/en-us/visualstudio/debugger/how-to-set-debug-and-release-configurations?view=vs-2022)
with options labeled `vcpkg-debug`, `vcpkg-release`, `default-debug`, and `default-release`.

**If you wish to build the project in *DEBUG* mode, select `default-debug` or `vcpkg-debug`**, recommended for developers and **running unit tests**.

**If you wish to build the project in *RELEASE* mode, select `default-release` or `vcpkg-release`**, recommended if you just want to check the game out.

#### Build the Project with Windows Terminal

First, create a `build/` directory for CMake and vcpkg in the root of the project directory (`Tetris/`).

```powershell
mkdir build/
cd build/
```

Assuming your terminal's `INCLUDE` path is set up correctly and you are able to use `cmake` as a command, you can execute:

> For debug mode
```powershell
cmake .. -DCMAKE_BUILD_TYPE="Debug"
```

> For release mode
```powershell
cmake .. -DCMAKE_BUILD_TYPE="Release"
```

### Building on Linux

First, create a `build/` directory for CMake and vcpkg in the root of the project directory (`Tetris/`).

```bash
mkdir build/
cd build/
```

Next, build the project using either of the following commands:

> For debug mode
```bash
cmake .. -DCMAKE_BUILD_TYPE="Debug"
```

> For release mode
```bash
cmake .. -DCMAKE_BUILD_TYPE="Release"
```

> Note: There isn't a build or release mode yet, so this should suffice
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build
```

# Running Unit Tests

A more in depth guide for running unit tests on Windows and Linux will be added later.

**If on Windows, the easiest way would be to use Visual Studio and selecting "Run All Tests" under the "Test" tab**.

# License

This project is open source and distributed under the MIT License.
