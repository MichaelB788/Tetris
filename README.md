# tetris-game

This project is a simple implementation of the classic Tetris game using C++ and the
SDL2 library.

The game features the traditional gameplay of Tetris, where the player controls falling
tetrominoes, rotating and placing them in a grid to complete full lines.

Completed lines are popped out of the stack.

## Features

- Tetrominoes (I, O, T, L, J, S, Z) that can be rotated and moved.

- Line clearing and score tracking.

- Game over condition when blocks reach the top of the screen.

- Keyboard controls.
 
## Requirements

### Software Dependencies:

- C++ compiler (e.g., g++, clang++)

- SDL2: Simple DirectMedia Layer 2.0 (for graphics, input, and window management)

- CMake

## Installation:

On Windows: Download the SDL2 development libraries from SDL's website.
Follow the setup guide for your compiler.

On macOS: You can install SDL2 via Homebrew:

`brew install sdl2`

On Linux: Install SDL2 through your package manager:

`sudo apt-get install libsdl2-dev`

Clone the repository:

``
git clone https://github.com/yourusername/tetris-clone.git
cd tetris-clone
``

Navigate to the project folder and create a build directory:

``
mkdir build
cd build
cmake ..
make
``

Run the game:

`./tetris`

# Controls

Arrow Keys:
- Left Arrow: Move the tetromino left.

- Right Arrow: Move the tetromino right.

- Down Arrow: Move the tetromino down faster (soft drop).

- Up Arrow: Rotate the tetromino.

- Spacebar: Hard drop (instantly drops the tetromino to the bottom).

- Esc: Quit the game.

# Project Structure

```bash
src
├── api
│   ├── Core.cpp                # Stores all SDL2 subsystems
│   ├── Core.hpp
│   └── sdl                     # Uses SDL2 and SDL_TTF font
│       ├── Font.cpp
│       ├── Font.hpp
│       ├── Renderer.cpp
│       ├── Renderer.hpp
│       ├── Window.cpp
│       └── Window.hpp
├── CMakeLists.txt
├── Components
│   ├── Context.cpp             # Stores visual resources and input handler
│   ├── Context.hpp
│   ├── Event
│   │   ├── Commands            # Commands are children of the base class Command.hpp
│   │   │   ├── Command.hpp
│   │   │   ├── Drop.cpp
│   │   │   ├── Drop.hpp
│   │   │   ├── Move.cpp
│   │   │   ├── Move.hpp
│   │   │   ├── Rotate.cpp
│   │   │   ├── Rotate.hpp
│   │   │   ├── Store.cpp
│   │   │   └── Store.hpp
│   │   ├── EventHandler.cpp    # Handles user input after polling events 
│   │   └── EventHandler.hpp
│   └── Visual 
│       ├── Draw.cpp
│       ├── Draw.hpp
│       ├── Graphics.cpp        # Handles graphical interface
│       ├── Graphics.hpp
│       ├── Text.cpp
│       └── Text.hpp
├── Game
│   ├── Mechanics.cpp           # Rules for tetromino
│   ├── Mechanics.hpp
│   ├── Objects
│   │   ├── Coordinate.cpp
│   │   ├── Coordinate.hpp
│   │   ├── Grid.cpp
│   │   ├── Grid.hpp
│   │   ├── Piece.cpp
│   │   └── Piece.hpp
│   ├── Tetris.cpp              # Game loop
│   ├── Tetris.hpp
│   └── Variables.hpp           # Global enums
└── main.cpp
```

# License

This project is open source and distributed under the MIT License.
