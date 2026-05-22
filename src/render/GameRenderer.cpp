#include "render/GameRenderer.hpp"
#include "core/Tetris.hpp"
#include "core/Tetromino.hpp"
#include "platform/PlatformSDL.hpp"
#include "util/Point.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

GameRenderer::GameRenderer(SDL_Renderer &renderer,
                           const std::filesystem::path &atlas_path,
                           float tile_size)
    : tile_size_(tile_size) {
  piece_atlas_.reset(IMG_LoadTexture(&renderer, atlas_path.c_str()));
  if (!piece_atlas_)
    throw SDL::Error("Could not load image atlas");
}

void GameRenderer::draw_snapshot(SDL_Renderer &renderer,
                                 const Tetris::Snapshot &snapshot) {
  draw_tetromino(renderer, snapshot.active, TetrominoRenderType::Normal,
                 game_layout.board);

  // Draw the ghost piece
  {
    auto ghost = snapshot.active;
    hard_drop(ghost, snapshot.matrix);
    draw_tetromino(renderer, ghost, TetrominoRenderType::Ghost,
                   game_layout.board);
  }

  draw_matrix(renderer, snapshot.matrix);

  if (snapshot.held.has_value()) {
    draw_tetromino(renderer, snapshot.held.value(), TetrominoRenderType::Normal,
                   game_layout.hold);
  }

  auto next_pos = game_layout.queue;
  for (const auto next_type : snapshot.seven_bag) {
    draw_tetromino(renderer, Tetromino{.type = next_type},
                   TetrominoRenderType::Normal, next_pos);
    next_pos = resolve(next_pos, {.y = 3});
  }
}

void GameRenderer::fit_within_window(SDL_Window &window) {
  // Center the board within the center of the screen
  {
    int w = 0, h = 0;
    SDL_GetWindowSizeInPixels(&window, &w, &h);
    game_layout.board = {.x = (w - (Matrix::COLS * tile_size_)) / 2,
                         .y = (h - (Matrix::ROWS * tile_size_)) / 2};
  }

  // All other ui elements are anchored off of the board's screen position
  game_layout.queue = resolve(game_layout.board, {.x = -4, .y = 3});
  game_layout.hold =
      resolve(game_layout.board, {.x = Matrix::COLS + 3, .y = 3});
}

auto GameRenderer::compute_hud_layout() const -> HudLayout {
  return {
      .next_label = resolve(game_layout.queue, {.x = -1, .y = -3}),
      .hold_label = resolve(game_layout.hold, {.x = -1, .y = -3}),
      .score_label = resolve(game_layout.hold, {.x = -1, .y = 4}),
      .score_value = resolve(game_layout.hold, {.x = -1, .y = 6}),
      .fps_label = resolve(game_layout.queue, {.x = -1, .y = 15}),
      .fps_value = resolve(game_layout.queue, {.x = -1, .y = 17}),
  };
}

void GameRenderer::draw_tetromino_tile(SDL_Renderer &renderer,
                                       Tetromino::Type type,
                                       TetrominoRenderType render_type,
                                       Point<int> pos, Point<float> offset) {
  // This rect acts sort of like an "index" to the texture atlas.
  const SDL_FRect tetromino_texture = {
      .x = tile_size_ * static_cast<float>(type),
      .y = render_type == TetrominoRenderType::Ghost ? tile_size_ : 0,
      .w = tile_size_,
      .h = tile_size_};
  // This rect is where the texture will be drawn on the screen.
  const SDL_FRect texture_position = {.x = (pos.x * tile_size_) + offset.x,
                                      .y = (pos.y * tile_size_) + offset.y,
                                      .w = tile_size_,
                                      .h = tile_size_};

  SDL_RenderTexture(&renderer, piece_atlas_.get(), &tetromino_texture,
                    &texture_position);
}

void GameRenderer::draw_tetromino(SDL_Renderer &renderer, Tetromino tetromino,
                                  TetrominoRenderType role,
                                  Point<float> offset) {
  for (auto pos : shape_of(tetromino)) {
    draw_tetromino_tile(renderer, tetromino.type, role, pos, offset);
  }
}

void GameRenderer::draw_matrix(SDL_Renderer &renderer, const Matrix &matrix) {
  // Draw all locked pieces
  {
    std::array<std::vector<Point<int>>, 7> grounded_rects;

    for (int y = 0; y < Matrix::ROWS; ++y) {
      for (int x = 0; x < Matrix::COLS; ++x) {
        if (auto tile = matrix.at(x, y)) {
          draw_tetromino_tile(renderer, tile.value(),
                              TetrominoRenderType::Normal, {x, y},
                              game_layout.board);
        }
      }
    }
  }

  // Draw the matrix outline
  {
    const SDL_FRect outline_rect = {.x = game_layout.board.x,
                                    .y = game_layout.board.y,
                                    .w = Matrix::COLS * tile_size_,
                                    .h = Matrix::ROWS * tile_size_};
    SDL_SetRenderDrawColor(&renderer, 0x54, 0x58, 0xCC, 0xFF);
    SDL_RenderRect(&renderer, &outline_rect);
  }
}
