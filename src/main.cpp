#include "AppState.hpp"
#include "PlatformSDL.hpp"
#include "ScreenPos.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <thread>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  const std::filesystem::path project_root = PROJECT_ROOT;

  *appstate = new AppState;
  AppState *state = static_cast<AppState *>(*appstate);

  // Window init
  state->window.reset(
      SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE));
  if (!state->window) {
    return SDL_APP_FAILURE;
  }

  // Renderer init
  state->renderer.reset(SDL_CreateRenderer(state->window.get(), nullptr));
  if (!state->renderer) {
    return SDL_APP_FAILURE;
  }

  // Texture atlas init
  const std::filesystem::path atlas_path =
      project_root / "assets" / "sprites" / "TetrominoAtlas.png";
  state->piece_atlas.reset(
      IMG_LoadTexture(state->renderer.get(), atlas_path.c_str()));
  if (!state->piece_atlas) {
    return SDL_APP_FAILURE;
  }

  // Text engine init
  state->text_engine.reset(TTF_CreateRendererTextEngine(state->renderer.get()));
  if (!state->text_engine) {
    return SDL_APP_FAILURE;
  }

  // Font init
  const std::filesystem::path font_path =
      project_root / "assets" / "font" / "Arcade-Classic.ttf";
  state->font.reset(TTF_OpenFont(font_path.c_str(), 32.00f));
  if (!state->font) {
    return SDL_APP_FAILURE;
  }

  // Fix offsets before starting
  ScreenPos::fit_offsets_within_window(state->pf_pos, state->text_pos,
                                       *state->window);

  // Init number renderer
  state->num_renderer =
      NumberRenderer(state->text_engine.get(), state->font.get());

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *state = static_cast<AppState *>(appstate);

  state->prev_time = state->curr_time;
  state->curr_time = std::chrono::steady_clock::now();
  const auto delta = state->curr_time - state->prev_time;

  state->handler.handle_kb_input(state->tetris, state->rng, delta);

  state->tetris.update(delta, state->rng);
  if (state->tetris.game_over())
    state->tetris = Tetris{state->rng};

  // render_frame();

  state->fps_counter.tick(delta);

  // If frame finished early, sleep for remainder of time
  {
    const auto frame_time = std::chrono::steady_clock::now() - state->curr_time;
    const auto frame_duration = state->fps.get_frame_duration();
    if (frame_time < frame_duration) {
      std::this_thread::sleep_for(frame_duration - frame_time);
    }
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *state = static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_WINDOW_RESIZED:
    ScreenPos::fit_offsets_within_window(state->pf_pos, state->text_pos,
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
    std::cerr << "An error occured: " << SDL_GetError() << "\n";
  }
}
