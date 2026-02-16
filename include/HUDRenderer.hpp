#ifndef TETRIS_HUD_RENDERER_HPP
#define TETRIS_HUD_RENDERER_HPP
#include "Tetromino.hpp"
#include <optional>

class SDL_Renderer;
class SDL_Texture;
class NextQueue;

class HUDRenderer {
public:
  HUDRenderer(SDL_Renderer *renderer, SDL_Texture *norm_atlas)
      : renderer_(renderer), norm_atlas_(norm_atlas) {}

  void draw_next_queue(const NextQueue &queue);

  void draw_held(const std::optional<Tetromino> &held);

  void wrap_around_board(Point board_pos);

private:
  SDL_Renderer *renderer_ = nullptr;

  SDL_Texture *norm_atlas_ = nullptr;

  Point queue_offset_{0, 0};

  Point hold_offset_{0, 0};
};

#endif
