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
  const std::filesystem::path project_root = PROJECT_ROOT;
  if (project_root.empty()) {
    std::println(std::cerr, "main: Project root not properly set!");
    return EXIT_FAILURE;
  }

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) || !TTF_Init()) {
    std::println(std::cerr, "main: {}", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Not a fan of the exception handling here, might change
  try {
    App app(project_root / "assets" / "sprites" / "TetrominoAtlas.png",
            project_root / "assets" / "font" / "PressStart2P" /
                "PressStart2P-vaV7.ttf");
    app.loop();
  } catch (std::exception &e) {
    std::println(std::cerr, "main: {}", e.what());
    return EXIT_FAILURE;
  }

  TTF_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
