#include "AppRenderer.hpp"
#include "Constants.hpp"
#include "Point.hpp"
#include "Tetris.hpp"
#include "TextRenderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace {
auto resolve(Point<float> base, Point<float> offset) -> Point<float> {
  return base + (offset * PIXEL_SCALE);
};
} // namespace

AppRenderer::AppRenderer(const std::filesystem::path &atlas_path,
                         const std::filesystem::path &font_path)
    : window(SDL_CreateWindow("Tetris", 900, 1000, SDL_WINDOW_RESIZABLE)),
      renderer(SDL_CreateRenderer(window.get(), nullptr)),
      texture_atlas(IMG_LoadTexture(renderer.get(), atlas_path.c_str())),
      text_renderer(*renderer, font_path) {
  if (!window) {
    throw std::runtime_error("Couldn't create window");
  } else if (!renderer) {
    throw std::runtime_error("Couldn't create renderer");
  } else if (!texture_atlas) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Center content before starting
  center_frame_within_window();
}

void AppRenderer::center_frame_within_window() {
  // Update window size
  {
    int w, h;
    SDL_GetWindowSize(window.get(), &w, &h);
    win_size.w = static_cast<float>(w);
    win_size.h = static_cast<float>(h);
  }

  section_matrix.x = (win_size.w - MATRIX_WIDTH) / 2;
  section_matrix.y = (win_size.h - MATRIX_HEIGHT) / 2;
  section_left = resolve(section_matrix, {-6, 0});
  section_right = resolve(section_matrix, {(MATRIX_COLS + 2), 0});
}

void AppRenderer::render_frame(Tetris &tetris) {
  SDL_SetRenderDrawColor(renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer.get());

  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    draw_game_objects(tetris);
    draw_game_text(tetris);
    break;
  case Paused:
    draw_centered_text("PAUSED");
    break;
  case GameOver:
    draw_centered_text("GAMEOVER!\n\nCONTINUE?\n\n[Y/N]");
    break;
  }

  SDL_RenderPresent(renderer.get());
}

void AppRenderer::draw_tile(Tetromino::Type type, Point<int> matrix_pos,
                            Point<float> screen_offset, Style style) const {
  const auto texture_rect_y = style == Style::Transparent ? PIXEL_SCALE : 0;
  const auto adjusted_pos =
      resolve(screen_offset, {.x = static_cast<float>(matrix_pos.x),
                              .y = static_cast<float>(matrix_pos.y)});

  const SDL_FRect texture_rect{.x = PIXEL_SCALE * static_cast<float>(type),
                               .y = texture_rect_y,
                               .w = PIXEL_SCALE,
                               .h = PIXEL_SCALE};
  const SDL_FRect texture_screen_pos{.x = adjusted_pos.x,
                                     .y = adjusted_pos.y,
                                     .w = PIXEL_SCALE,
                                     .h = PIXEL_SCALE};
  SDL_RenderTexture(renderer.get(), texture_atlas.get(), &texture_rect,
                    &texture_screen_pos);
}

void AppRenderer::draw_tetromino(Tetromino tet, Point<float> screen_offset,
                                 Style style) const {
  for (const auto pos : tet.get_shape()) {
    draw_tile(tet.get_type(), pos, screen_offset, style);
  }
}

void AppRenderer::draw_matrix(const Matrix &matrix,
                              Point<float> screen_offset) const {
  for (int y = 0; y < MATRIX_ROWS; ++y)
    for (int x = 0; x < MATRIX_COLS; ++x)
      if (auto tile = matrix.at(x, y))
        draw_tile(tile.value(), {x, y}, screen_offset, Style::Filled);

  const SDL_FRect outline_rect{.x = screen_offset.x,
                               .y = screen_offset.y,
                               .w = MATRIX_COLS * PIXEL_SCALE,
                               .h = MATRIX_ROWS * PIXEL_SCALE};
  SDL_SetRenderDrawColor(renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(renderer.get(), &outline_rect);
}

void AppRenderer::draw_game_objects(const Tetris &tetris) const {
  draw_tetromino(tetris.get_ghost_piece(), section_matrix, Style::Transparent);
  draw_tetromino(tetris.get_active_piece(), section_matrix, Style::Filled);
  draw_matrix(tetris.get_matrix(), section_matrix);

  const auto held_pos = resolve(section_right, {1, 3});
  if (const auto held_piece = tetris.get_held_piece()) {
    draw_tetromino({held_piece.value()}, held_pos, Style::Filled);
  }

  auto next_pos = resolve(section_left, {1, 3});
  for (const auto next_type : tetris.get_seven_bag()) {
    draw_tetromino({next_type}, next_pos, Style::Filled);
    next_pos.y += 3 * PIXEL_SCALE;
  }
}

void AppRenderer::draw_game_text(const Tetris &tetris) {
  text_renderer.draw_text("NEXT", section_left);
  text_renderer.draw_text("HOLD", section_right);
  text_renderer.draw_text("SCORE", resolve(section_right, {0, 8}));
  text_renderer.draw_num(tetris.get_score(), resolve(section_right, {0, 10}));
}

void AppRenderer::draw_centered_text(std::string_view str) {
  const auto text_size = text_renderer.get_text_size(str);
  const Point pos{.x = (win_size.w - text_size.w) / 2,
                  .y = (win_size.h - text_size.h) / 2};
  text_renderer.draw_text(str, pos);
}
