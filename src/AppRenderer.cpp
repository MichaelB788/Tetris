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
    : window_(SDL_CreateWindow("Tetris", 800, 800, SDL_WINDOW_RESIZABLE)),
      renderer_(SDL_CreateRenderer(window_.get(), nullptr)),
      texture_atlas_(IMG_LoadTexture(renderer_.get(), atlas_path.c_str())),
      text_renderer_(*renderer_, font_path) {
  if (!window_) {
    throw std::runtime_error("Couldn't create window");
  } else if (!renderer_) {
    throw std::runtime_error("Couldn't create renderer");
  } else if (!texture_atlas_) {
    throw std::runtime_error("Couldn't create renderer");
  }

  // Center content before starting
  center_frame_within_window();
}

void AppRenderer::center_frame_within_window() {
  auto &[w, h] = win_size_;
  SDL_GetWindowSize(window_.get(), &w, &h);

  section_matrix_.x = (w - MATRIX_WIDTH) / 2;
  section_matrix_.y = (h - MATRIX_HEIGHT) / 2;
  section_left_ = resolve(section_matrix_, {.x = -6});
  section_right_ = resolve(section_matrix_, {.x = MATRIX_COLS + 2});
}

void AppRenderer::render_frame(Tetris &tetris) {
  SDL_SetRenderDrawColor(renderer_.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer_.get());

  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    draw_game_objects(tetris);
    draw_screen_text(tetris);
    break;
  case Paused: {
    auto [win_w, win_h] = win_size_;
    auto [tex_w, tex_h] = text_renderer_.get_text_size("PAUSED");
    Point pos{.x = (static_cast<float>(win_w - tex_w)) / 2,
              .y = (static_cast<float>(win_h - tex_h)) / 2};
    text_renderer_.draw_text("PAUSED", pos);
  } break;
  case GameOver:
    break;
  }

  SDL_RenderPresent(renderer_.get());
}

void AppRenderer::draw_tile(Tetromino::Type type, Point<int> matrix_pos,
                            Point<float> screen_offset, Style style) const {
  const auto y_coord = style == Style::Transparent ? PIXEL_SCALE : 0;
  const SDL_FRect texture_rect = {.x = PIXEL_SCALE * static_cast<float>(type),
                                  .y = y_coord,
                                  .w = PIXEL_SCALE,
                                  .h = PIXEL_SCALE};

  const SDL_FRect texture_screen_pos = {
      .x = static_cast<float>(matrix_pos.x) * PIXEL_SCALE + screen_offset.x,
      .y = static_cast<float>(matrix_pos.y) * PIXEL_SCALE + screen_offset.y,
      .w = PIXEL_SCALE,
      .h = PIXEL_SCALE};

  SDL_RenderTexture(renderer_.get(), texture_atlas_.get(), &texture_rect,
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

  const SDL_FRect outline_rect = {.x = screen_offset.x,
                                  .y = screen_offset.y,
                                  .w = MATRIX_COLS * PIXEL_SCALE,
                                  .h = MATRIX_ROWS * PIXEL_SCALE};
  SDL_SetRenderDrawColor(renderer_.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(renderer_.get(), &outline_rect);
}

void AppRenderer::draw_game_objects(const Tetris &tetris) const {
  draw_tetromino(tetris.get_ghost_piece(), section_matrix_, Style::Transparent);
  draw_tetromino(tetris.get_active_piece(), section_matrix_, Style::Filled);
  draw_matrix(tetris.get_matrix(), section_matrix_);

  const auto held_pos = resolve(section_right_, {.x = 1, .y = 3});
  if (const auto held_piece = tetris.get_held_piece()) {
    draw_tetromino({held_piece.value()}, held_pos, Style::Filled);
  }

  auto next_pos = resolve(section_left_, {.x = 1, .y = 3});
  for (const auto next_type : tetris.get_seven_bag()) {
    draw_tetromino({next_type}, next_pos, Style::Filled);
    next_pos.y += 3 * PIXEL_SCALE;
  }
}

void AppRenderer::draw_screen_text(const Tetris &tetris) {
  text_renderer_.draw_text("NEXT", section_left_);
  text_renderer_.draw_text("HOLD", section_right_);
  text_renderer_.draw_text("SCORE", resolve(section_right_, {.y = 8}));
  text_renderer_.draw_num(tetris.get_score(),
                          resolve(section_right_, {.y = 10}));
}
