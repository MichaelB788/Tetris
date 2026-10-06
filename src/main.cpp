#include "App.hpp"
#include <SDL3/SDL_error.h>
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
      throw std::runtime_error(std::string("SDL_Init: ") + SDL_GetError());
    if (!TTF_Init())
      throw std::runtime_error(std::string("TTF_Init: ") + SDL_GetError());

    App{project_root / "assets" / "sprites" / "TetrominoAtlas.png",
        project_root / "assets" / "font" / "PressStart2P" /
            "PressStart2P-vaV7.ttf"}
        .loop();
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
  }

  TTF_Quit();
  SDL_Quit();
}
