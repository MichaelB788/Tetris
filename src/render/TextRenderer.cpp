#include "render/TextRenderer.hpp"
#include "render/TetrisGameRenderer.hpp"
#include "render/Tetris_Paint.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <cstddef>
#include <vector>

TextRenderer::TextRenderer(const std::filesystem::path &font_path,
                           int font_size, SDL_Renderer *renderer)
    : text_engine_(sdl::ttf::create_renderer_text_engine(renderer)),
      font_(sdl::ttf::open_font(font_path, font_size)) {
  // Create screen text objects.
  screen_text_.score_.text =
      sdl::ttf::create_text(text_engine_.get(), font_.get(), "SCORE");
  screen_text_.next_.text =
      sdl::ttf::create_text(text_engine_.get(), font_.get(), "NEXT");
  screen_text_.hold_.text =
      sdl::ttf::create_text(text_engine_.get(), font_.get(), "HOLD");

  // Cache digit textures.
  static constexpr std::array<const char *, 10> NUMS_STR{
      "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < 10; ++i) {
    nums_[i] =
        sdl::ttf::create_text(text_engine_.get(), font_.get(), NUMS_STR[i]);
  }
}

void TextRenderer::render_screen_text() {
  render_text(screen_text_.next_);
  render_text(screen_text_.stored_);
  render_text(screen_text_.hold_);
  render_text(screen_text_.score_);
}

void TextRenderer::render_text(const TextObj &text_obj) {
  auto &[x, y] = text_obj.pos;
  TTF_DrawRendererText(text_obj.text.get(), x, y);
}

void TextRenderer::render_score_int(int score) {
  // Align position to be under SCORE text
  auto [x, y] = screen_text_.score_.pos;
  y += tetris::paint::TILE_SIZE * 2;

  // If the score is only one digit, we can exit early
  if (score < 10) {
    TTF_DrawRendererText(nums_[score].get(), x, y);
    return;
  }

  // Make sure space between all didits is equal.
  int text_width;
  TTF_GetTextSize(nums_[0].get(), &text_width, NULL);

  // Push all digits onto a stack
  std::vector<int> score_digits{};
  while (score > 0) {
    score_digits.push_back(score % 10);
    score /= 10;
  }

  // Render the digits. LIFO ensures consecutive digits are rendered from left
  // to right.
  while (!score_digits.empty()) {
    TTF_DrawRendererText(nums_[score_digits.back()].get(), x, y);
    score_digits.pop_back();
    x += text_width;
  }
}

void TextRenderer::align_with_game(const TetrisGameRenderer &game_renderer) {
  auto game_pos = game_renderer.get_positions();

  auto &[next_x, next_y] = screen_text_.next_.pos;
  auto &[score_x, score_y] = screen_text_.score_.pos;
  auto &[hold_x, hold_y] = screen_text_.hold_.pos;

  next_x = game_pos.queue.x - tetris::paint::TILE_SIZE;
  next_y = game_pos.queue.y - tetris::paint::TILE_SIZE * 3;

  score_x = hold_x = game_pos.hold.x - tetris::paint::TILE_SIZE;
  hold_y = game_pos.hold.y - tetris::paint::TILE_SIZE * 3;
  score_y = game_pos.hold.y + tetris::paint::TILE_SIZE * 4;
}
