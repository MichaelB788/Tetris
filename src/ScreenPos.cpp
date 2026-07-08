#include "ScreenPos.hpp"
#include "Constants.hpp"
#include <SDL3/SDL_video.h>

auto resolve(Point<float> base, Point<float> offset) -> Point<float> {
  return base + (offset * PIXEL_SCALE);
}

void ScreenPos::fit_offsets_within_window(ScreenPos::Playfield &pf_pos,
                                          ScreenPos::Text &text_pos,
                                          SDL_Window &win) {
  int w = 0, h = 0;
  SDL_GetWindowSize(&win, &w, &h);

  pf_pos.board.x = (w - (MATRIX_COLS * PIXEL_SCALE)) / 2;
  pf_pos.board.y = (h - (MATRIX_ROWS * PIXEL_SCALE)) / 2;

  pf_pos.seven_bag_pos = resolve(pf_pos.board, {.x = -4, .y = 3});
  pf_pos.held_piece = resolve(pf_pos.board, {.x = MATRIX_COLS + 3, .y = 3});

  text_pos.next = resolve(pf_pos.seven_bag_pos, {.x = -1, .y = -3});
  text_pos.hold = resolve(pf_pos.held_piece, {.x = -1, .y = -3});
  text_pos.score_label = resolve(pf_pos.held_piece, {.x = -1, .y = 4});
  text_pos.score_val = resolve(pf_pos.held_piece, {.x = -1, .y = 6});
  text_pos.fps_label = resolve(pf_pos.seven_bag_pos, {.x = -1, .y = 15});
  text_pos.fps_val = resolve(pf_pos.seven_bag_pos, {.x = -1, .y = 17});
}
