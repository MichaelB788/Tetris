#include "render/BoardRenderer.hpp"
#include "core/Matrix.hpp"
#include "core/Playfield.hpp"
#include <SDL3/SDL_render.h>

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

void BoardRenderer::draw_playfield(const Playfield &playfield) {
  tetris::paint::tetromino(playfield.player(), renderer_, *atlas_, board_pos_);
  tetris::paint::tetromino(playfield.ghost(), renderer_, *ghost_atlas_,
                           board_pos_);
  tetris::paint::matrix(playfield.matrix(), renderer_, *atlas_, board_pos_);
}

void BoardRenderer::center_within_window(int win_w, int win_h) {
  board_pos_.x = (win_w - (Matrix::COLS * tetris::paint::TILE_SIZE)) / 2;
  board_pos_.y = (win_h - (Matrix::ROWS * tetris::paint::TILE_SIZE)) / 2;
}
