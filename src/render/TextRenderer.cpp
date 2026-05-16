#include "render/TextRenderer.hpp"
#include "platform/PlatformSDL_TTF.hpp"
#include "render/TetrisGameRenderer.hpp"
#include "render/Tetris_Paint.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <cstddef>
#include <vector>

TextRenderer::TextRenderer(const std::filesystem::path &font_path,
                           int font_size, SDL_Renderer *renderer)
    : text_engine_(TTF_CreateRendererTextEngine(renderer)),
      font_(TTF_OpenFont(font_path.c_str(), font_size)) {
  // Create screen text objects.
  score_.text.reset(
      TTF_CreateText(text_engine_.get(), font_.get(), "SCORE", 0));
  next_.text.reset(TTF_CreateText(text_engine_.get(), font_.get(), "NEXT", 0));
  hold_.text.reset(TTF_CreateText(text_engine_.get(), font_.get(), "HOLD", 0));

  // Cache digit textures.
  static constexpr std::array<const char *, 10> NUMS_STR{
      "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < 10; ++i) {
    nums_[i].reset(
        TTF_CreateText(text_engine_.get(), font_.get(), NUMS_STR[i], 0));
  }
}

void TextRenderer::render_screen_text() {
  render_text(next_);
  render_text(stored_);
  render_text(hold_);
  render_text(score_);
}

void TextRenderer::render_text(const TextObj &text_obj) {
  auto &[x, y] = text_obj.pos;
  TTF_DrawRendererText(text_obj.text.get(), x, y);
}

void TextRenderer::render_score_int(int score) {
  // Align position to be under SCORE text
  auto [x, y] = score_.pos;
  y += TILE_SIZE * 2;

  // If the score is only one digit, we can exit early
  if (score < 10) {
    TTF_DrawRendererText(nums_[score].get(), x, y);
    return;
  }

  // Push all digits onto a stack
  std::vector<int> score_digits{};
  while (score > 0) {
    score_digits.push_back(score % 10);
    score /= 10;
  }

  // Make sure space between all didits is equal.
  int text_width;
  TTF_GetTextSize(nums_[0].get(), &text_width, NULL);

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

  auto &[next_x, next_y] = next_.pos;
  auto &[score_x, score_y] = score_.pos;
  auto &[hold_x, hold_y] = hold_.pos;

  next_x = game_pos.queue.x - TILE_SIZE;
  next_y = game_pos.queue.y - TILE_SIZE * 3;

  score_x = hold_x = game_pos.hold.x - TILE_SIZE;
  hold_y = game_pos.hold.y - TILE_SIZE * 3;
  score_y = game_pos.hold.y + TILE_SIZE * 4;
}
