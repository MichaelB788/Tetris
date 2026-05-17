#include "render/TetrisGameRenderer.hpp"
#include "core/TetrisGame.hpp"
#include "platform/PlatformSDL.hpp"
#include "render/Tetris_Paint.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

TetrisGameRenderer::TetrisGameRenderer(const std::filesystem::path &atlas_path,
                                       SDL_Renderer *renderer)
    : piece_atlas_(IMG_LoadTexture(renderer, atlas_path.c_str())) {
  Surface ghost_surf{IMG_Load(atlas_path.c_str())};
  SDL_SetSurfaceAlphaMod(ghost_surf.get(), 0x80);
  ghost_atlas_.reset(SDL_CreateTextureFromSurface(renderer, ghost_surf.get()));
}

void TetrisGameRenderer::draw_frame(const TetrisGame &game,
                                    SDL_Renderer &renderer) {
  const auto snapshot = game.snapshot();
  // Draw the main board
  {
    tetris::paint::tetromino(snapshot.active, pos_.board, renderer,
                             *piece_atlas_);
    // Draw the ghost piece
    {
      auto ghost = snapshot.active;
      hard_drop(ghost, snapshot.matrix);
      tetris::paint::tetromino(ghost, pos_.board, renderer, *ghost_atlas_);
    }
    tetris::paint::matrix(snapshot.matrix, pos_.board, renderer, *piece_atlas_);
  }
  // Draw the HUD elements
  {
    tetris::paint::tetromino(Tetromino(snapshot.next_queue.peek()), pos_.queue,
                             renderer, *piece_atlas_);

    if (snapshot.held.has_value()) {
      tetris::paint::tetromino(snapshot.held.value(), pos_.hold, renderer,
                               *piece_atlas_);
    }
  }
}

void TetrisGameRenderer::align_inside_rect(std::pair<int, int> rect) {
  auto &[board_x, board_y] = pos_.board;
  auto &[queue_x, queue_y] = pos_.queue;
  auto &[hold_x, hold_y] = pos_.hold;

  const auto [w, h] = rect;
  board_x = (w - (Matrix::COLS * TILE_SIZE)) / 2;
  board_y = (h - (Matrix::ROWS * TILE_SIZE)) / 2;

  queue_x = board_x - (4 * TILE_SIZE);

  hold_x = board_x + ((Matrix::COLS + 3) * TILE_SIZE);

  queue_y = hold_y = board_y + TILE_SIZE;
}
