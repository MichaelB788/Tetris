#pragma once
#include "core/Tetris.hpp"
#include "platform/PlatformSDL.hpp"

class NextQueue;

class HUDRenderer {
public:
  HUDRenderer(const std::filesystem::path &path_to_atlas,
              SDL_Renderer &renderer)
      : renderer_(renderer),
        atlas_(PlatformSDL::create_texture_from_img(renderer, path_to_atlas)) {}

  void draw_next_queue(const NextQueue &queue);

  void draw_held(const HeldTetromino &held);

  void wrap_around_board(Point board_pos);

  [[nodiscard]] Point queue_offset() const { return queue_offset_; }

  [[nodiscard]] Point hold_offset() const { return hold_offset_; }

private:
  SDL_Renderer &renderer_;

  PlatformSDL::Texture atlas_;

  Point queue_offset_{0, 0};

  Point hold_offset_{0, 0};
};
