#include "HUDRenderer.hpp"
#include "NextQueue.hpp"
#include "pixel.hpp"

void HUDRenderer::draw_next_queue(const NextQueue &queue) {
  Point origin = queue_offset_;
  for (const auto &tetromino : queue) {
    Tetromino::Projection tet = tetromino.projection();
    for (const auto &block : tet.blocks)
      pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                                 pixel::texture_src(tet.type), block, origin);
    origin -= {.x = 0, .y = -100};
  }
}

void HUDRenderer::draw_held(const std::optional<Tetromino> &hold) {
  if (hold.has_value()) {
    Tetromino::Projection tet = hold.value().projection();
    for (const auto &block : tet.blocks)
      pixel::draw_tetromino_tile(renderer_, norm_atlas_,
                                 pixel::texture_src(tet.type), block,
                                 queue_offset_);
  }
}
