#include "render/HUDRenderer.hpp"
#include "core/Matrix.hpp"
#include "core/Tetris.hpp"
#include "render/tetris-paint.hpp"

void HUDRenderer::draw_hud(const HUD &hud) {
  tetris::paint::tetromino(Tetromino(hud.next_queue.peek()), renderer_, *atlas_,
                           queue_offset_);

  if (hud.held_type.has_value()) {
    tetris::paint::tetromino(Tetromino(hud.held_type.value()), renderer_,
                             *atlas_, hold_offset_);
  }
}

void HUDRenderer::wrap_around_board(Point board_pos) {
  queue_offset_.x = board_pos.x - (4 * tetris::paint::TILE_SIZE);
  hold_offset_.x =
      board_pos.x + ((Matrix::COLS + 3) * tetris::paint::TILE_SIZE);
  queue_offset_.y = hold_offset_.y = board_pos.y + tetris::paint::TILE_SIZE;
}
