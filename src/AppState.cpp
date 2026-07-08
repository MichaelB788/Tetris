#include "AppState.hpp"
#include "Constants.hpp"
#include "SDL3/SDL_render.h"
#include "TetrisRenderer.hpp"
#include <SDL3/SDL_video.h>

void render_game_obj(AppState &state) {
  TetrisRenderer::draw_ghost(state.tetris.ghost_piece(), state.pf_pos.board,
                             *state.renderer, *state.texture_atlas);

  TetrisRenderer::draw_tetromino(state.tetris.active_piece(),
                                 state.pf_pos.board, *state.renderer,
                                 *state.texture_atlas);

  TetrisRenderer::draw_matrix(state.tetris.matrix(), state.pf_pos.board,
                              *state.renderer, *state.texture_atlas);

  if (state.tetris.held_piece().has_value()) {
    TetrisRenderer::draw_tetromino(state.tetris.held_piece().value(),
                                   state.pf_pos.held_piece, *state.renderer,
                                   *state.texture_atlas);
  }

  auto next_pos = state.pf_pos.seven_bag_pos;
  for (const auto next_type : state.tetris.seven_bag()) {
    TetrisRenderer::draw_tetromino(Tetromino(next_type), next_pos,
                                   *state.renderer, *state.texture_atlas);
    next_pos.y += 3 * PIXEL_SCALE;
  }
}

void render_screen_text(AppState &state) {
  state.text_renderer.render_text("NEXT", state.text_pos.next,
                                  *state.text_engine, *state.font);
  state.text_renderer.render_text("HOLD", state.text_pos.hold,
                                  *state.text_engine, *state.font);
  state.text_renderer.render_text("SCORE", state.text_pos.score_label,
                                  *state.text_engine, *state.font);
  state.text_renderer.render_text("FPS", state.text_pos.fps_label,
                                  *state.text_engine, *state.font);
}

void render_screen_int(AppState &state) {
  state.num_renderer.render_num(state.tetris.score(), state.text_pos.score_val);
  state.num_renderer.render_num(state.fps_counter.get_current_fps(),
                                state.text_pos.fps_val);
}

void render_frame(AppState &state) {
  SDL_SetRenderDrawColor(state.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(state.renderer.get());

  render_game_obj(state);
  render_screen_text(state);
  render_screen_int(state);

  SDL_RenderPresent(state.renderer.get());
}
