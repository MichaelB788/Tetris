#include "AppState.hpp"
#include "Constants.hpp"
#include "SDL3/SDL_render.h"
#include "TetrisRenderer.hpp"
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <stdexcept>
#include <thread>

AppState::AppState(const Configuration &config) {
  // Window init
  window.reset(SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE));
  if (!window) {
    throw std::runtime_error("Couldn't create window");
  }

  // Renderer init
  renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
  if (!renderer) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Texture atlas init
  texture_atlas.reset(
      IMG_LoadTexture(renderer.get(), config.atlas_path.c_str()));
  if (!texture_atlas) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Text engine init
  text_engine.reset(TTF_CreateRendererTextEngine(renderer.get()));
  if (!text_engine) {
    throw std::runtime_error("Couldn't create text engine");
  }

  // Font init
  font.reset(TTF_OpenFont(config.font_path.c_str(), FONT_SCALE));
  if (!font) {
    throw std::runtime_error("Couldn't create text engine");
  }

  // Number renderer init
  num_renderer = NumberRenderer(text_engine.get(), font.get());

  // Fix offsets before starting
  screen_pos::fit_offsets_within_window(pf_pos, text_pos, *window);
}

void AppState::listen_to_keyboard_input() {
  handler.listen_to_keyboard_input();
}

void AppState::tick() {
  prev_time = curr_time;
  curr_time = std::chrono::steady_clock::now();
  const auto delta = curr_time - prev_time;

  fps_counter.tick(delta);

  if (tetris.get_state() == Tetris::State::Running) {
    tetris.tick(delta, rng);
    handler.handle_repeated_events(tetris, rng, delta);
  }
}

void AppState::handle_tetris_state() {
  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
  case Paused:
    handler.handle_new_events(tetris, rng);
    break;
  case GameOver: // TODO: Add option to continue/quit
    tetris.reset(rng);
    break;
    break;
  }
}

void AppState::render_game_objects() const {
  // clang-format off
  tetris::renderer::draw_ghost(tetris.get_ghost_piece(), pf_pos.board, *renderer, *texture_atlas);
  tetris::renderer::draw_tetromino(tetris.get_active_piece(), pf_pos.board, *renderer, *texture_atlas);
  tetris::renderer::draw_matrix(tetris.get_matrix(), pf_pos.board, *renderer, *texture_atlas);

  if (const auto held_piece = tetris.get_held_piece()) {
    tetris::renderer::draw_tetromino({held_piece.value()}, pf_pos.held_piece, *renderer, *texture_atlas);
  }

  auto next_pos = pf_pos.seven_bag_pos;
  for (const auto next_type : tetris.get_seven_bag()) {
    tetris::renderer::draw_tetromino({next_type}, next_pos, *renderer, *texture_atlas);
    next_pos.y += 3 * PIXEL_SCALE;
  }
  // clang-format on
}

void AppState::render_screen_text() {
  text_renderer.render_text("NEXT", text_pos.next, *text_engine, *font);
  text_renderer.render_text("HOLD", text_pos.hold, *text_engine, *font);
  text_renderer.render_text("SCORE", text_pos.score_label, *text_engine, *font);
  text_renderer.render_text("FPS", text_pos.fps_label, *text_engine, *font);
}

void AppState::render_screen_numbers() const {
  num_renderer.render_num(tetris.get_score(), text_pos.score_val);
  num_renderer.render_num(fps_counter.get_current_fps(), text_pos.fps_val);
}

void AppState::render_frame() {
  SDL_SetRenderDrawColor(renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer.get());

  render_game_objects();
  render_screen_text();
  render_screen_numbers();

  SDL_RenderPresent(renderer.get());
}

void AppState::sleep_thread() const {
  const auto frame_time = std::chrono::steady_clock::now() - curr_time;
  const auto frame_duration = fps.get_frame_duration();
  if (frame_time < frame_duration) {
    std::this_thread::sleep_for(frame_duration - frame_time);
  }
}

void AppState::handle_window_resize_event() {
  screen_pos::fit_offsets_within_window(pf_pos, text_pos, *window);
}
