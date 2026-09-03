#include "RenderingModule.hpp"
#include "Constants.hpp"
#include "GameTextRenderer.hpp"
#include "Piece.hpp"
#include "Point.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <format>

namespace {
auto resolve(FPoint base, FPoint offset) -> FPoint {
  return fpoint::add(base, fpoint::multiply_scalar(offset, PIXEL_SCALE));
};
} // namespace

RenderingModule::RenderingModule(const std::filesystem::path &atlas_path,
                                 const std::filesystem::path &font_path) {
  window.reset(SDL_CreateWindow("Tetris", 900, 1000, SDL_WINDOW_RESIZABLE));
  if (!window) {
    throw std::runtime_error(
        std::format("RenderingModule::window: {}", SDL_GetError()));
  }

  renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
  if (!renderer) {
    throw std::runtime_error(
        std::format("RenderingModule::renderer: {}", SDL_GetError()));
  }

  texture_atlas.reset(IMG_LoadTexture(renderer.get(), atlas_path.c_str()));
  if (!texture_atlas) {
    throw std::runtime_error(
        std::format("RenderingModule::texture_atlas: {}", SDL_GetError()));
  }

  text_renderer = GameTextRenderer(*renderer, font_path);

  // Center content before starting
  fit_context_within_window();
}

void RenderingModule::fit_context_within_window() {
  // Update window size
  int w, h;
  SDL_GetWindowSize(window.get(), &w, &h);
  win_size.w = static_cast<float>(w);
  win_size.h = static_cast<float>(h);

  section_matrix.x = (win_size.w - MATRIX_WIDTH) / 2;
  section_matrix.y = (win_size.h - MATRIX_HEIGHT) / 2;
  section_left = resolve(section_matrix, {-6, 0});
  section_right = resolve(section_matrix, {(MATRIX_COLS + 2), 0});
}

void RenderingModule::render_frame(const Tetris &tetris) {
  SDL_SetRenderDrawColor(renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(renderer.get());

  switch (tetris.get_state()) {
    using enum Tetris::State;
  case Running:
    render_game_state(tetris);
    break;
  case Paused:
    text_renderer.draw_centered_game_text(GameText::Paused, win_size);
    break;
  case GameOver:
    text_renderer.draw_centered_game_text(GameText::GameOver, win_size);
    break;
  }

  SDL_RenderPresent(renderer.get());
}

void RenderingModule::render_game_state(const Tetris &tetris) {
  auto draw_tile = [this](Piece::Type type, FPoint screen_position,
                          BlockStyle style) {
    const auto texture_rect_y = style == BlockStyle::Ghost ? PIXEL_SCALE : 0;

    const SDL_FRect texture_rect{.x = PIXEL_SCALE * static_cast<float>(type),
                                 .y = texture_rect_y,
                                 .w = PIXEL_SCALE,
                                 .h = PIXEL_SCALE};
    const SDL_FRect texture_screen_pos{.x = screen_position.x,
                                       .y = screen_position.y,
                                       .w = PIXEL_SCALE,
                                       .h = PIXEL_SCALE};
    SDL_RenderTexture(renderer.get(), texture_atlas.get(), &texture_rect,
                      &texture_screen_pos);
  };

  auto draw_piece = [&](const Piece &pc, FPoint screen_position,
                        BlockStyle style) {
    for (const auto tetr_pos : piece::create_shape(pc))
      draw_tile(pc.type, resolve(screen_position, tetr_pos), style);
  };

  // Draw the ghost piece
  // NOTE: This should always be called before drawing active
  draw_piece(tetris.get_ghost_piece(), section_matrix, BlockStyle::Ghost);

  // Draw the active Tetromino
  draw_piece(tetris.get_active_piece(), section_matrix, BlockStyle::Solid);

  // Draw the held piece
  if (const auto held_type = tetris.get_held_piece())
    draw_piece({held_type.value()}, resolve(section_right, {1, 3}),
               BlockStyle::Solid);

  // Draw the seven bag queue
  auto next_pos = resolve(section_left, {1, 3});
  for (const auto next_type : tetris.get_seven_bag()) {
    draw_piece({next_type}, next_pos, BlockStyle::Solid);
    next_pos.y += 3 * PIXEL_SCALE;
  }

  // Draw grounded tiles
  for (float y = 0; y < MATRIX_ROWS; ++y) {
    for (float x = 0; x < MATRIX_COLS; ++x) {
      if (auto tile = tetris.get_matrix().at(x, y)) {
        draw_tile(tile.value(), resolve(section_matrix, {x, y}),
                  BlockStyle::Solid);
      }
    }
  }

  // Draw the Matrix border
  const SDL_FRect outline_rect{.x = section_matrix.x,
                               .y = section_matrix.y,
                               .w = MATRIX_WIDTH,
                               .h = MATRIX_HEIGHT};
  SDL_SetRenderDrawColor(renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(renderer.get(), &outline_rect);

  // Draw game text
  text_renderer.draw_game_text(GameText::Next, section_left);
  text_renderer.draw_game_text(GameText::Hold, section_right);
  text_renderer.draw_game_text(GameText::Score, resolve(section_right, {0, 8}));
  text_renderer.draw_unsigned_integer(tetris.get_score(),
                                      resolve(section_right, {0, 10}));
}
