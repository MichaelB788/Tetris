#include "core/TetrisApp.hpp"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_pixels.h>

void TetrisApp::run() {
  while (!event_handler_.should_quit()) {
    process_input();
    update_state();
    center_layout();
    render_frame();
    sleep(std::chrono::milliseconds(12));
  }
}

void TetrisApp::render_frame() {
  static const auto [r, g, b, a] = SDL_Color(0x17, 0x18, 0x28, 0xFF);
  SDL_SetRenderDrawColor(renderer_.get(), r, g, b, a);
  SDL_RenderClear(renderer_.get());

  hud_renderer_.draw_hud(tetris_.hud());

  board_renderer_.draw_board(tetris_.board());

  text_renderer_.render_text();
  text_renderer_.render_score(tetris_.score());

  SDL_RenderPresent(renderer_.get());
}

void TetrisApp::update_state() {
  update_gravity();
  handle_tetris_state();
}

void TetrisApp::update_gravity() {
  gravity_clock_.tick();

  if (gravity_clock_.has_set_off()) {
    tetris_.move_down();
    gravity_clock_.reset();
  }

  update_level();
}

void TetrisApp::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array<std::pair<unsigned, std::chrono::milliseconds>,
                              10>
      levels{{
          {10, 1000ms},
          {20, 900ms},
          {30, 800ms},
          {40, 700ms},
          {50, 600ms},
          {60, 500ms},
          {70, 450ms},
          {80, 400ms},
          {90, 300ms},
          {100, 200ms},
      }};

  unsigned score = tetris_.score();

  auto it = std::ranges::find_if(
      levels, [score](const auto &entry) { return score < entry.first; });

  if (it != std::end(levels))
    gravity_clock_.activate_in(it->second);
  else
    gravity_clock_.activate_in(100ms);
}

void TetrisApp::handle_tetris_state() {
  if (tetris_.status() == Status::GameOver)
    tetris_ = {};
}

void TetrisApp::center_layout() {
  board_renderer_.center_within_window(win_w, win_h);
  hud_renderer_.wrap_around_board(board_renderer_.pos());
  text_renderer_.adjust_lhs(hud_renderer_.queue_offset());
  text_renderer_.adjust_rhs(hud_renderer_.hold_offset());
}

void TetrisApp::reset() {
  tetris_ = {};
  gravity_clock_ = Clock(std::chrono::milliseconds(1000));
}
