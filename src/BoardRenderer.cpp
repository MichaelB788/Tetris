#include "BoardRenderer.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include "pixel.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

BoardRenderer::BoardRenderer(const std::filesystem::path &path_to_atlas,
                             SDL_Renderer &renderer)
    : renderer_(renderer),
      atlas_(PlatformSDL::create_texture_from_img(renderer_, path_to_atlas)) {
  PlatformSDL::Surface ghost_surf =
      PlatformSDL::create_surface_from_img(path_to_atlas.c_str());

  SDL_SetSurfaceAlphaMod(ghost_surf.get(), 100);

  ghost_atlas_ =
      PlatformSDL::create_texture_from_surface(renderer_, *ghost_surf);
}

void BoardRenderer::draw_current(const Tetromino &current) {
  for (const auto &block : current.shape())
    pixel::draw_tetromino_tile(renderer_, *atlas_,
                               pixel::textures_src[current.type()], block,
                               offset_);
}

void BoardRenderer::draw_ghost(const Tetromino &ghost) {
  for (const auto &block : ghost.shape())
    pixel::draw_tetromino_tile(renderer_, *ghost_atlas_,
                               pixel::textures_src[ghost.type()], block,
                               offset_);
}

void BoardRenderer::draw_matrix(const Matrix &matrix) {
  std::array<std::vector<Point>, 8> grounded_rects;

  for (int y = 0; y < Matrix::ROWS; ++y) {
    for (int x = 0; x < Matrix::COLS; ++x) {
      Point curr = {x, y};
      if (matrix.at(curr).has_value())
        pixel::draw_tetromino_tile(renderer_, *atlas_,
                                   pixel::textures_src[matrix.at(curr).value()],
                                   curr, offset_);
    }
  }

  draw_matrix_outline();
}

void BoardRenderer::draw_matrix_outline() {
  const SDL_FRect outline = {.x = static_cast<float>(offset_.x),
                             .y = static_cast<float>(offset_.y),
                             .w = Matrix::COLS * pixel::SIZE,
                             .h = Matrix::ROWS * pixel::SIZE};
  static constexpr SDL_Color purple = {
      .r = 0x54, .g = 0x58, .b = 0xCC, .a = 0xFF};

  SDL_SetRenderDrawColor(&renderer_, purple.r, purple.g, purple.b, purple.a);
  SDL_RenderRect(&renderer_, &outline);
}

void BoardRenderer::center_within_window(int win_w, int win_h) {
  offset_.x = (win_w - (Matrix::COLS * pixel::SIZE)) / 2;
  offset_.y = (win_h - (Matrix::ROWS * pixel::SIZE)) / 2;
}
