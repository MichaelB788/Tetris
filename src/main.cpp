#include "AppState.hpp"
#include "ScreenPos.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <thread>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  const std::filesystem::path project_root = PROJECT_ROOT;

  // SDL subsystems init
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) || !TTF_Init()) {
    return SDL_APP_FAILURE;
  }

  try {
    *appstate = new AppState(
        {.atlas_path =
             project_root / "assets" / "sprites" / "TetrominoAtlas.png",
         .font_path = project_root / "assets" / "font" / "Arcade-Classic.ttf",
         .custom_controls_path = argv[1] ? argv[1] : ""});
    auto state = static_cast<AppState *>(*appstate);
  } catch (std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  auto state = static_cast<AppState *>(appstate);

  state->prev_time = state->curr_time;
  state->curr_time = std::chrono::steady_clock::now();
  const auto delta = state->curr_time - state->prev_time;

  appstate::handle_tetris_state(*state, delta);
  appstate::render_frame(*state);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  auto state = static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_WINDOW_RESIZED:
    screen_pos::fit_offsets_within_window(state->pf_pos, state->text_pos,
                                          *state->window);
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
