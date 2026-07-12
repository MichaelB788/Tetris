#include "AppState.hpp"
#include "Constants.hpp"
#include "SDL3/SDL_render.h"
#include "TetrisRenderer.hpp"
#include <SDL3/SDL_video.h>
#include <chrono>

void appstate::handle_tetris_state(AppState &state,
                                   std::chrono::nanoseconds delta) {
  switch (state.tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    state.handler.handle_kb_input(state.tetris, state.rng, delta);
    state.tetris.tick(delta, state.rng);
    break;
  case GameOver: // TODO: Add option to continue/quit
    state.tetris.reset(state.rng);
    break;
  case Paused:
    break;
  }
}

namespace {
// clang-format off
void render_game_objects(AppState &state) {
  tetris::renderer::draw_ghost(state.tetris.get_ghost_piece(), state.pf_pos.board, *state.renderer, *state.texture_atlas);
  tetris::renderer::draw_tetromino(state.tetris.get_active_piece(), state.pf_pos.board, *state.renderer, *state.texture_atlas);
  tetris::renderer::draw_matrix(state.tetris.get_matrix(), state.pf_pos.board, *state.renderer, *state.texture_atlas);

  if (const auto held_piece = state.tetris.get_held_piece()) {
    tetris::renderer::draw_tetromino({state.tetris.get_held_piece().value()}, state.pf_pos.held_piece, *state.renderer, *state.texture_atlas);
  }

  auto next_pos = state.pf_pos.seven_bag_pos;
  for (const auto next_type : state.tetris.get_seven_bag()) {
    tetris::renderer::draw_tetromino({next_type}, next_pos, *state.renderer, *state.texture_atlas);
    next_pos.y += 3 * PIXEL_SCALE;
  }
}

void render_screen_text(AppState &state) {
  state.text_renderer.render_text("NEXT", state.text_pos.next, *state.text_engine, *state.font);
  state.text_renderer.render_text("HOLD", state.text_pos.hold, *state.text_engine, *state.font);
  state.text_renderer.render_text("SCORE", state.text_pos.score_label, *state.text_engine, *state.font);
  state.text_renderer.render_text("FPS", state.text_pos.fps_label, *state.text_engine, *state.font);
}

void render_screen_numbers(AppState &state) {
  state.num_renderer.render_num(state.tetris.get_score(), state.text_pos.score_val);
  state.num_renderer.render_num(state.fps_counter.get_current_fps(), state.text_pos.fps_val);
}
// clang-format on
} // namespace

void appstate::render_frame(AppState &state) {
  SDL_SetRenderDrawColor(state.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(state.renderer.get());

  render_game_objects(state);
  render_screen_text(state);
  render_screen_numbers(state);

  SDL_RenderPresent(state.renderer.get());
}
