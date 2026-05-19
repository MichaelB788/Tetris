#include "core/App.hpp"
#include "platform/PlatformSDL.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>

int main() {
  try {
    const std::filesystem::path project_root = PROJECT_ROOT;
    if (SDL_Init(SDL_INIT_VIDEO) && TTF_Init()) {
      TetrisApp(
          {.controls = project_root / "controls.ini",
           .tetromino_atlas =
               project_root / "assets" / "sprites" / "TetrominoAtlas.png",
           .font_path = project_root / "assets" / "font" / "Arcade-Classic.ttf",
           .target_fps = 60})
          .run();
    } else {
      throw SDL::Error("Failed to initialize SDL");
    }
  } catch (const std::exception &exception) {
    std::cerr << exception.what() << std::endl;
  }

  TTF_Quit();
  SDL_Quit();
}
