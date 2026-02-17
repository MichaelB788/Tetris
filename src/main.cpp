#include "PlatformSDL.hpp"
#include "TetrisApp.hpp"
#include <iostream>

int main(const int argc, const char **argv) {
  try {
    PlatformSDL platform{};

    TetrisApp tetris({.controls = "controls.ini",
                      .tetromino_atlas = "assets/sprites/tetromino.png",
                      .font_path = "assets/font/Arcade-Classic.ttf",
                      .font_size = 36,
                      .gravity_rate = std::chrono::milliseconds(1000)});

    tetris.run();
  } catch (const ExceptionSDL &exception) {
    std::cerr << exception.what() << std::endl;
  } catch (const std::invalid_argument &exception) {
    std::cerr << "Invalid argument encountered: " << exception.what()
              << std::endl;
  }

  return 0;
}
