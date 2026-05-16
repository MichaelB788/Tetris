#include "core/TetrisApp.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>

int main() {
  try {
    const std::filesystem::path project_root = PROJECT_ROOT;
    if (SDL_Init(SDL_INIT_VIDEO) && TTF_Init()) {
      TetrisApp(
          {.controls = project_root / "controls.ini",
           .tetromino_atlas =
               project_root / "assets" / "sprites" / "tetromino.png",
           .font_path = project_root / "assets" / "font" / "Arcade-Classic.ttf",
           .font_size = 36,
           .target_fps = 60})
          .run();
    } else {
      throw std::runtime_error("Failed to initialize SDL");
    }
  } catch (const std::invalid_argument &exception) {
    std::cerr << "Invalid argument encountered: " << exception.what()
              << std::endl;
  } catch (const std::exception &exception) {
    std::cerr << "Encountered exception: " << exception.what() << std::endl;
  }

  TTF_Quit();
  SDL_Quit();
}
