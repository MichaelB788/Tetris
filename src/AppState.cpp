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
  window_.reset(SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE));
  if (!window_) {
    throw std::runtime_error("Couldn't create window");
  }

  // Renderer init
  renderer_.reset(SDL_CreateRenderer(window_.get(), nullptr));
  if (!renderer_) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Texture atlas init
  texture_atlas_.reset(
      IMG_LoadTexture(renderer_.get(), config.atlas_path.c_str()));
  if (!texture_atlas_) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Text engine init
  text_engine_.reset(TTF_CreateRendererTextEngine(renderer_.get()));
  if (!text_engine_) {
    throw std::runtime_error("Couldn't create text engine");
  }

  // Font init
  font_.reset(TTF_OpenFont(config.font_path.c_str(), FONT_SCALE));
  if (!font_) {
    throw std::runtime_error("Couldn't create text engine");
  }

  // Number renderer init
  num_renderer_ = NumberRenderer(text_engine_.get(), font_.get());

  // Fix offsets before starting
  screen_pos::fit_offsets_within_window(pf_pos_, text_pos_, *window_);
}

void AppState::listen_to_keyboard_input() {
  handler_.listen_to_keyboard_input();
}

void AppState::tick() {
  prev_time_ = curr_time_;
  curr_time_ = std::chrono::steady_clock::now();
  const auto delta = curr_time_ - prev_time_;

  fps_counter_.tick(delta);

  if (tetris_.get_state() == Tetris::State::Running) {
    tetris_.tick(delta, rng_);
    handler_.handle_repeated_events(tetris_, rng_, delta);
  }
}

void AppState::handle_tetris_state() {
  switch (tetris_.get_state()) {
    using enum Tetris::State;
  case Running:
  case Paused:
    handler_.handle_new_events(tetris_, rng_);
    break;
  case GameOver: // TODO: Add option to continue/quit
    tetris_.reset(rng_);
    break;
    break;
  }
}

// clang-format off
void AppState::render_game_objects() const {
  tetris::renderer::draw_ghost(tetris_.get_ghost_piece(), pf_pos_.board, *renderer_, *texture_atlas_);
  tetris::renderer::draw_tetromino(tetris_.get_active_piece(), pf_pos_.board, *renderer_, *texture_atlas_);
  tetris::renderer::draw_matrix(tetris_.get_matrix(), pf_pos_.board, *renderer_, *texture_atlas_);

  if (const auto held_piece = tetris_.get_held_piece()) {
    tetris::renderer::draw_tetromino({held_piece.value()}, pf_pos_.held_piece, *renderer_, *texture_atlas_);
  }

  auto next_pos = pf_pos_.seven_bag_pos;
  for (const auto next_type : tetris_.get_seven_bag()) {
    tetris::renderer::draw_tetromino({next_type}, next_pos, *renderer_, *texture_atlas_);
    next_pos.y += 3 * PIXEL_SCALE;
  }
}

void AppState::render_screen_text() {
  text_renderer_.render_text("NEXT", text_pos_.next, *text_engine_, *font_);
  text_renderer_.render_text("HOLD", text_pos_.hold, *text_engine_, *font_);
  text_renderer_.render_text("SCORE", text_pos_.score_label, *text_engine_, *font_);
  text_renderer_.render_text("FPS", text_pos_.fps_label, *text_engine_, *font_);
}
// clang-format on

void AppState::render_screen_numbers() const {
  num_renderer_.render_num(tetris_.get_score(), text_pos_.score_val);
  num_renderer_.render_num(fps_counter_.get_current_fps(), text_pos_.fps_val);
}

void AppState::render_frame() {
  SDL_SetRenderDrawColor(renderer_.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer_.get());

  render_game_objects();
  render_screen_text();
  render_screen_numbers();

  SDL_RenderPresent(renderer_.get());
}

void AppState::sleep_thread() const {
  const auto frame_time = std::chrono::steady_clock::now() - curr_time_;
  const auto frame_duration = fps_.get_frame_duration();
  if (frame_time < frame_duration) {
    std::this_thread::sleep_for(frame_duration - frame_time);
  }
}

void AppState::handle_window_resize_event() {
  screen_pos::fit_offsets_within_window(pf_pos_, text_pos_, *window_);
}
