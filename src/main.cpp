#include "PlatformSDL.hpp"
#include "TetrisApp.hpp"
#include <filesystem>
#include <iostream>
#include <optional>

int main(const int argc, const char **argv) {
  std::optional<std::filesystem::path> controls =
      (argc > 1) ? std::make_optional(argv[1]) : std::nullopt;

  try {
    PlatformSDL platform{};

    TetrisApp tetris({.platform = platform,
                      .controls = controls,
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
