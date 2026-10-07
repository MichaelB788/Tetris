#include "GameTextRenderer.hpp"
#include "Constants.hpp"
#include "PlatformSDL.hpp"
#include "Size.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <vector>

GameTextRenderer::GameTextRenderer(SDL_Renderer &renderer,
                                   const std::filesystem::path &font_path) {
  if (engine.reset(TTF_CreateRendererTextEngine(&renderer)); engine == nullptr)
    throw SDL::Exception("TTF_CreateRendererTextEngine");

  if (font.reset(TTF_OpenFont(font_path.c_str(), FONT_SCALE)); font == nullptr)
    throw SDL::Exception("TTF_OpenFont");

  static constexpr std::array text_str{"NEXT", "HOLD", "SCORE", "PAUSED",
                                       "GAMEOVER!\n\nCONTINUE?\n\n[Y/N]"};
  for (size_t i = 0; i < text_map.size(); ++i) {
    if (text_map[i].reset(
            TTF_CreateText(engine.get(), font.get(), text_str[i], 0));
        text_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText text_str");
  }

  static constexpr std::array nums_str{'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};
  for (size_t i = 0; i < nums_map.size(); ++i) {
    if (nums_map[i].reset(
            TTF_CreateText(engine.get(), font.get(), &nums_str[i], 1));
        nums_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText nums_map");
  }
}

void GameTextRenderer::draw_game_text(TextIdx i, FPoint pos) {
  TTF_DrawRendererText(text_map[static_cast<size_t>(i)].get(), pos.x, pos.y);
}

void GameTextRenderer::draw_game_text_centered(TextIdx i, FSize window) {
  int w, h;
  TTF_GetTextSize(text_map[static_cast<size_t>(i)].get(), &w, &h);
  TTF_DrawRendererText(text_map[static_cast<size_t>(i)].get(),
                       (window.w - static_cast<float>(w)) / 2,
                       (window.h - static_cast<float>(h)) / 2);
}

void GameTextRenderer::draw_uint(unsigned n, FPoint pos) const {
  // Draw a single digit
  if (n < 10) {
    TTF_DrawRendererText(nums_map[n].get(), pos.x, pos.y);
    return;
  }

  // N consists of multiple digits, so we need to push all digits of N onto a
  // stack
  std::vector<unsigned> digits{};
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }

  // Render each digit individually
  while (!digits.empty()) {
    TTF_DrawRendererText(nums_map[digits.back()].get(), pos.x, pos.y);
    digits.pop_back();
    pos.x += FONT_SCALE;
  }
}
