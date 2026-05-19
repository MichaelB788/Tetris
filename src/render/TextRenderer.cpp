#include "render/TextRenderer.hpp"
#include "platform/PlatformSDL.hpp"
#include "platform/PlatformSDL_TTF.hpp"
#include "util/Point.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

TextRenderer::TextRenderer(SDL_Renderer &renderer,
                           const std::filesystem::path &font_path,
                           float font_size)
    : font_size_(font_size) {
  text_engine_.reset(TTF_CreateRendererTextEngine(&renderer));
  if (!text_engine_)
    throw SDL::Error("Error creating text engine");

  font_.reset(TTF_OpenFont(font_path.c_str(), font_size));
  if (!font_)
    throw SDL::Error("Error opening font");

  {
    static constexpr std::array<const char *, 10> NUM_STR{
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for (size_t i = 0; i < nums_text_.size(); ++i) {
      nums_text_[i].reset(
          TTF_CreateText(text_engine_.get(), font_.get(), NUM_STR[i], 1));
    }
  }
}

void TextRenderer::render_text(std::string_view str, Point<float> pos) {
  if (!cached_text_.contains(str)) {
    cached_text_[str] = SDL::TTF::Text{
        TTF_CreateText(text_engine_.get(), font_.get(), str.data(), 0)};
  }
  TTF_DrawRendererText(cached_text_[str].get(), pos.x, pos.y);
}

void TextRenderer::render_int(int num, Point<float> pos) const {
  // Check if only a single digit to render
  if (num < 10) {
    TTF_DrawRendererText(nums_text_[num].get(), pos.x, pos.y);
    return;
  }

  // Render each individual digit
  {
    std::vector<int> digits{};
    while (num > 0) {
      digits.push_back(num % 10);
      num /= 10;
    }
    while (!digits.empty()) {
      TTF_DrawRendererText(nums_text_[digits.back()].get(), pos.x, pos.y);
      digits.pop_back();
      pos.x += font_size_;
    }
  }
}

/*
void TextRenderer::align_with_game(const GameRenderer &game_renderer) {
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
*/
