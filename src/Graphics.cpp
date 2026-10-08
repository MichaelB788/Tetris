#include "Graphics.hpp"
#include "Piece.hpp"
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stack>
#include <vector>

namespace {
constexpr float PIXL_SZ = 32;
constexpr float FONT_SZ = PIXL_SZ;
constexpr float MATRIX_PIXL_WIDTH = Matrix::COLS * PIXL_SZ;
constexpr float MATRIX_PIXL_HEIGHT = Matrix::ROWS * PIXL_SZ;

auto resolve(FPoint base, FPoint offset) -> FPoint {
  return fpoint::add(base, fpoint::multiply_scalar(offset, PIXL_SZ));
}

void draw_block(Graphics::SDL_Ctx &sdl, Piece::Type type, FPoint pos,
                BlockStyle style) {
  const SDL_FRect src_rect{.x = PIXL_SZ * static_cast<float>(type),
                           .y = static_cast<float>(style),
                           .w = PIXL_SZ,
                           .h = PIXL_SZ};
  const SDL_FRect dst_rect{pos.x, pos.y, PIXL_SZ, PIXL_SZ};
  SDL_RenderTexture(sdl.renderer.get(), sdl.piece_atlas.get(), &src_rect,
                    &dst_rect);
}
} // namespace

Graphics::Graphics(const std::filesystem::path &atlas_texture_path,
                   const std::filesystem::path &font_path) {
  graphics::sdl::ctx_init(sdl, atlas_texture_path);
  graphics::ttf::ctx_init(ttf, *sdl.renderer, font_path);
  fit_context_within_window();
}

void Graphics::fit_context_within_window() {
  // Update window size
  int w, h;
  SDL_GetWindowSize(sdl.window.get(), &w, &h);
  window_size.w = static_cast<float>(w);
  window_size.h = static_cast<float>(h);

  layout.matrix.x = (window_size.w - MATRIX_PIXL_WIDTH) / 2;
  layout.matrix.y = (window_size.h - MATRIX_PIXL_HEIGHT) / 2;
  layout.left = resolve(layout.matrix, {.x = -6});
  layout.right = resolve(layout.matrix, {.x = Matrix::COLS + 2});
}

void Graphics::render_frame(const Tetris &tetris) {
  SDL_SetRenderDrawColor(sdl.renderer.get(), 0x17, 0x18, 0x28, 0xFF);
  SDL_RenderClear(sdl.renderer.get());

  switch (tetris.get_state()) {
  case Tetris::State::Running: {
    // render pieces
    graphics::sdl::draw_piece(sdl, tetris.get_active_piece(), layout.matrix,
                              BlockStyle::Solid);
    graphics::sdl::draw_piece(sdl, tetris.get_ghost_piece(), layout.matrix,
                              BlockStyle::Ghost);
    if (const auto held_type = tetris.get_held_piece_type()) {
      graphics::sdl::draw_piece(sdl, {held_type.value()},
                                resolve(layout.right, {1, 3}),
                                BlockStyle::Solid);
    }
    auto next_pos = resolve(layout.left, {1, 3});
    for (const auto next_type : tetris.get_seven_bag_preview()) {
      graphics::sdl::draw_piece(sdl, {next_type}, next_pos, BlockStyle::Solid);
      next_pos = resolve(next_pos, {.y = 3});
    }

    // render matrix
    graphics::sdl::draw_matrix(sdl, tetris.get_matrix(), layout.matrix);

    // render game text
    graphics::ttf::draw_text(ttf, GameText::Next, layout.left);
    graphics::ttf::draw_text(ttf, GameText::Hold, layout.right);
    graphics::ttf::draw_text(ttf, GameText::Score,
                             resolve(layout.right, {0, 8}));
    graphics::ttf::draw_uint(ttf, tetris.get_score(),
                             resolve(layout.right, {0, 10}));

  } break;
  case Tetris::State::Paused:
    graphics::ttf::draw_centered_text(ttf, GameText::Paused, window_size);
    break;
  case Tetris::State::GameOver:
    graphics::ttf::draw_centered_text(ttf, GameText::GameOver, window_size);
    break;
  }

  SDL_RenderPresent(sdl.renderer.get());
}

void graphics::sdl::ctx_init(Graphics::SDL_Ctx &sdl,
                             const std::filesystem::path &atlas_texture_path) {
  if (sdl.window.reset(
          SDL_CreateWindow("Tetris", 900, 1000, SDL_WINDOW_RESIZABLE));
      sdl.window == nullptr)
    throw SDL::Exception("SDL_CreateWindow");

  if (sdl.renderer.reset(SDL_CreateRenderer(sdl.window.get(), nullptr));
      sdl.renderer == nullptr)
    throw SDL::Exception("SDL_CreateRenderer");

  if (sdl.piece_atlas.reset(
          IMG_LoadTexture(sdl.renderer.get(), atlas_texture_path.c_str()));
      sdl.piece_atlas == nullptr)
    throw SDL::Exception("IMG_LoadTexture");
}

void graphics::sdl::draw_piece(Graphics::SDL_Ctx &sdl, Piece piece, FPoint base,
                               BlockStyle style) {
  for (const auto pos : piece::create_shape(piece))
    draw_block(sdl, piece.type, resolve(base, pos), style);
}

void graphics::sdl::draw_matrix(Graphics::SDL_Ctx &sdl, const Matrix &matrix,
                                FPoint base) {
  for (float y = 0; y < Matrix::ROWS; ++y) {
    for (float x = 0; x < Matrix::COLS; ++x) {
      if (auto tile = matrix.at(x, y)) {
        draw_block(sdl, tile.value(), resolve(base, {x, y}), BlockStyle::Solid);
      }
    }
  }

  const SDL_FRect outline_rect{base.x, base.y, MATRIX_PIXL_WIDTH,
                               MATRIX_PIXL_HEIGHT};
  SDL_SetRenderDrawColor(sdl.renderer.get(), 0x54, 0x58, 0xCC, 0xFF);
  SDL_RenderRect(sdl.renderer.get(), &outline_rect);
}

void graphics::ttf::ctx_init(Graphics::TTF_Ctx &ttf, SDL_Renderer &renderer,
                             const std::filesystem::path &font_path) {
  if (ttf.engine.reset(TTF_CreateRendererTextEngine(&renderer));
      ttf.engine == nullptr)
    throw SDL::Exception("TTF_CreateRendererTextEngine");

  if (ttf.font.reset(TTF_OpenFont(font_path.c_str(), FONT_SZ));
      ttf.font == nullptr)
    throw SDL::Exception("TTF_OpenFont");

  static constexpr std::array text_str{"NEXT", "HOLD", "SCORE", "PAUSED",
                                       "GAMEOVER!\n\nCONTINUE?\n\n[Y/N]"};
  for (size_t i = 0; i < ttf.game_text_map.size(); ++i) {
    if (ttf.game_text_map[i].reset(
            TTF_CreateText(ttf.engine.get(), ttf.font.get(), text_str[i], 0));
        ttf.game_text_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText text_str");
  }

  static constexpr std::array nums_str{'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};
  for (size_t i = 0; i < ttf.uint_text_map.size(); ++i) {
    if (ttf.uint_text_map[i].reset(
            TTF_CreateText(ttf.engine.get(), ttf.font.get(), &nums_str[i], 1));
        ttf.uint_text_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText uint_text");
  }
}

void graphics::ttf::draw_uint(Graphics::TTF_Ctx &ttf, unsigned n, FPoint pos) {
  if (n < 10) {
    TTF_DrawRendererText(ttf.uint_text_map[n].get(), pos.x, pos.y);
    return;
  }

  std::stack<unsigned, std::vector<unsigned>> digits{};
  while (n > 0) {
    digits.push(n % 10);
    n /= 10;
  }

  while (!digits.empty()) {
    TTF_DrawRendererText(ttf.uint_text_map[digits.top()].get(), pos.x, pos.y);
    digits.pop();
    pos.x += FONT_SZ;
  }
}

void graphics::ttf::draw_text(Graphics::TTF_Ctx &ttf, GameText game_text,
                              FPoint pos) {
  TTF_DrawRendererText(ttf.game_text_map[static_cast<size_t>(game_text)].get(),
                       pos.x, pos.y);
}

void graphics::ttf::draw_centered_text(Graphics::TTF_Ctx &ttf, GameText i,
                                       FSize window_size) {
  int text_w, text_h;
  TTF_GetTextSize(ttf.game_text_map[static_cast<size_t>(i)].get(), &text_w,
                  &text_h);
  TTF_DrawRendererText(ttf.game_text_map[static_cast<size_t>(i)].get(),
                       (window_size.w - static_cast<float>(text_w)) / 2,
                       (window_size.h - static_cast<float>(text_h)) / 2);
}
