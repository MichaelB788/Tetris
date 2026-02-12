#include "SDLPlatform.hpp"
#include "TetrisApp.hpp"
#include <memory>

int main(const int argc, const char **argv) {
  std::optional<std::filesystem::path> controls =
      (argc > 1) ? std::make_optional(argv[1]) : std::nullopt;

  auto platform = std::make_unique<SDLPlatform>();

  Backends backends = platform->create_backends();
  if (backends.window == nullptr || backends.renderer == nullptr)
    return 1;

  TetrisApp tetris({.window = std::move(backends.window),
                    .renderer = std::move(backends.renderer),
                    .controls = std::move(controls),
                    .gravity_rate = std::chrono::milliseconds(1000)});
  tetris.run();

  return 0;
}
