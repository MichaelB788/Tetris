#include "App.hpp"
#include "PlatformSDL.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>

int main() {
  const auto project_root = std::filesystem::path(PROJECT_ROOT);
  if (project_root.empty()) {
    std::cerr << "Project root not properly set" << std::endl;
    return 1;
  }

  try {
    if (!SDL_Init(SDL_INIT_VIDEO))
      throw SDL::Exception("SDL_Init");
    if (!TTF_Init())
      throw SDL::Exception("TTF_Init");

    App{project_root / "assets" / "sprites" / "TetrominoAtlas.png",
        project_root / "assets" / "font" / "PressStart2P" /
            "PressStart2P-vaV7.ttf"}
        .loop();
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
  } catch (...) {
    std::cerr << "An exception occurred" << std::endl;
  }

  TTF_Quit();
  SDL_Quit();
}
