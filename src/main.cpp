#include "App.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <print>

int main() {
  // Sanity check
  const std::filesystem::path project_root = PROJECT_ROOT;
  if (project_root.empty()) {
    std::println(std::cerr, "main: Project root not properly set!");
    return EXIT_FAILURE;
  }

  // Initialize SDL subsystems
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    std::println(std::cerr, "SDL_Init: {}", SDL_GetError());
    return EXIT_FAILURE;
  }
  if (!TTF_Init()) {
    std::println(std::cerr, "TTF_Init: {}", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  // Creating and running the application
  auto exit = EXIT_SUCCESS;
  try {
    App{project_root / "assets" / "sprites" / "TetrominoAtlas.png",
        project_root / "assets" / "font" / "PressStart2P" /
            "PressStart2P-vaV7.ttf"}
        .loop();
  } catch (const std::exception &err) {
    std::println(std::cerr, "{}", err.what());
    exit = EXIT_FAILURE;
  }

  // SDL subsystem cleanup
  TTF_Quit();
  SDL_Quit();

  return exit;
}
