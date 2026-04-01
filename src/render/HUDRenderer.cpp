#include "render/HUDRenderer.hpp"
#include "core/Matrix.hpp"

void HUDRenderer::wrap_around_board(Point board_pos) {
  queue_offset_.x = board_pos.x - (4 * tetris::paint::TILE_SIZE);
  hold_offset_.x =
      board_pos.x + ((Matrix::COLS + 3) * tetris::paint::TILE_SIZE);
  queue_offset_.y = hold_offset_.y = board_pos.y + tetris::paint::TILE_SIZE;
}
