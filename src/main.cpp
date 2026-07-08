#include "AppState.hpp"
#include "PlatformSDL.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>

// SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE)
// SDL_CreateRenderer(window_.get(), nullptr)

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  const std::filesystem::path project_root = PROJECT_ROOT;
  const AppState::FilePaths conf = {
      .controls = project_root / "controls.ini",
      .tetromino_atlas =
          project_root / "assets" / "sprites" / "TetrominoAtlas.png",
      .font = project_root / "assets" / "font" / "Arcade-Classic.ttf",
      .target_fps = 60};

  AppState *state = new AppState(conf);
}

int main() {
  try {
    if (SDL_Init(SDL_INIT_VIDEO) && TTF_Init()) {
      AppState({}).run();
    } else {
      throw SDL::Error("Failed to initialize SDL");
    }
  } catch (const std::exception &exception) {
    std::cerr << exception.what() << std::endl;
  }

  TTF_Quit();
  SDL_Quit();
}
