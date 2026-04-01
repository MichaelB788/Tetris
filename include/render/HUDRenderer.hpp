#pragma once
#include "core/NextQueue.hpp"
#include "core/Tetromino.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/tetris-paint.hpp"
#include <optional>

class HUDRenderer {
public:
  HUDRenderer(const std::filesystem::path &path_to_atlas,
              SDL_Renderer &renderer)
      : renderer_(renderer),
        atlas_(PlatformSDL::create_texture_from_img(renderer, path_to_atlas)) {}

  void draw_next(const NextQueue &queue) {
    tetris::paint::tetromino(Tetromino(queue.peek()), renderer_, *atlas_,
                             queue_offset_);
  }

  void draw_held(const std::optional<Tetromino::Type> &held) {
    if (held.has_value())
      tetris::paint::tetromino(Tetromino(held.value()), renderer_, *atlas_,
                               hold_offset_);
  }

  void wrap_around_board(Point board_pos);

  [[nodiscard]] Point queue_offset() const { return queue_offset_; }

  [[nodiscard]] Point hold_offset() const { return hold_offset_; }

private:
  SDL_Renderer &renderer_;

  PlatformSDL::Texture atlas_;

  Point queue_offset_{0, 0};

  Point hold_offset_{0, 0};
};
