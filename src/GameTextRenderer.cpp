#include "GameTextRenderer.hpp"
#include "Constants.hpp"
#include "Size.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <utility>
#include <vector>

GameTextRenderer::GameTextRenderer(SDL_Renderer &renderer,
                                   const std::filesystem::path &font_path)
    : engine(TTF_CreateRendererTextEngine(&renderer)),
      font(TTF_OpenFont(font_path.c_str(), FONT_SCALE)), text_map() {
  if (!engine) {
    throw std::runtime_error("Couldn't create text engine");
  } else if (!font) {
    throw std::runtime_error("Couldn't create font");
  }

  const std::array text_str{"NEXT", "HOLD", "SCORE", "PAUSED",
                            "GAMEOVER!\n\nCONTINUE?\n\n[Y/N]"};
  for (size_t i = 0; i < text_map.size(); ++i) {
    text_map[i].reset(TTF_CreateText(engine.get(), font.get(), text_str[i], 0));
  }

  const std::array nums_str{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < nums_map.size(); ++i)
    nums_map[i].reset(TTF_CreateText(engine.get(), font.get(), nums_str[i], 1));
}

void GameTextRenderer::draw_game_text(GameText msg, FPoint pos) {
  TTF_DrawRendererText(text_map[std::to_underlying(msg)].get(), pos.x, pos.y);
}

void GameTextRenderer::draw_unsigned_integer(unsigned n, FPoint pos) const {
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

void GameTextRenderer::draw_centered_game_text(GameText txt,
                                               Size<float> window) {
  Size<int> text_size = {};
  TTF_GetTextSize(text_map[std::to_underlying(txt)].get(), &text_size.w,
                  &text_size.h);
  TTF_DrawRendererText(text_map[std::to_underlying(txt)].get(),
                       (window.w - static_cast<float>(text_size.w)) / 2,
                       (window.h - static_cast<float>(text_size.h)) / 2);
}
