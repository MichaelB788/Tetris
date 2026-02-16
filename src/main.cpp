#include "PlatformSDL.hpp"
#include "TetrisApp.hpp"
#include <SDL3/SDL_init.h>
#include <filesystem>
#include <iostream>
#include <optional>

int main(const int argc, const char **argv) {
  std::optional<std::filesystem::path> controls =
      (argc > 1) ? std::make_optional(argv[1]) : std::nullopt;

  try {
    PlatformSDL platform{};

    TetrisApp tetris({.platform = platform,
                      .controls = std::move(controls),
                      .gravity_rate = std::chrono::milliseconds(1000)});

    tetris.run();
  } catch (const ExceptionSDL exception) {
    std::cerr << exception.what() << std::endl;
  }

  return 0;
}
