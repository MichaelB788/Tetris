#include "AppState.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  const std::filesystem::path project_root = PROJECT_ROOT;

  // SDL subsystems init
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) || !TTF_Init()) {
    return SDL_APP_FAILURE;
  }

  try {
    *appstate =
        new AppState(project_root / "assets" / "sprites" / "TetrominoAtlas.png",
                     project_root / "assets" / "font" / "PressStart2P" /
                         "PressStart2P-vaV7.ttf");
  } catch (std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  auto &state = *static_cast<AppState *>(appstate);

  state.tick();
  state.listen_to_keyboard_input();
  state.handle_tetris_state();
  state.render_frame();
  state.sleep_thread();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto &state = *static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_WINDOW_RESIZED:
    state.handle_window_resize_event();
    return SDL_APP_CONTINUE;
  default:
    return SDL_APP_CONTINUE;
  }
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  delete static_cast<AppState *>(appstate);

  TTF_Quit();
  SDL_Quit();

  if (result == SDL_APP_SUCCESS) {
    std::cout << "App closed successfully\n";
  } else if (result == SDL_APP_FAILURE) {
    std::cerr << "An error occurred: " << SDL_GetError() << "\n";
  }
}
