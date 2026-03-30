#include "render/HUDRenderer.hpp"
#include "core/NextQueue.hpp"
#include "core/Tetris.hpp"
#include "render/pixel.hpp"

void HUDRenderer::draw_next_queue(const NextQueue &next_queue) {
  Point offset = queue_offset_;
  for (const auto &type : next_queue.buffer()) {
    Tetromino tetromino = Tetromino(type);
    for (const auto &block : tetromino.shape())
      pixel::draw_tetromino_tile(renderer_, *atlas_,
                                 pixel::texture_src(tetromino.type()), block,
                                 offset);
    offset -= {.x = 0, .y = -100};
  }
}

void HUDRenderer::draw_held(const HeldTetromino &hold) {
  if (hold.type.has_value()) {
    Tetromino tetromino = Tetromino(hold.type.value());
    for (const auto &block : tetromino.shape())
      pixel::draw_tetromino_tile(renderer_, *atlas_,
                                 pixel::texture_src(tetromino.type()), block,
                                 hold_offset_);
  }
}

void HUDRenderer::wrap_around_board(Point board_pos) {
  queue_offset_.x = board_pos.x - (4 * pixel::SIZE);
  hold_offset_.x = board_pos.x + ((Matrix::COLS + 3) * pixel::SIZE);
  queue_offset_.y = hold_offset_.y = board_pos.y + pixel::SIZE;
}
