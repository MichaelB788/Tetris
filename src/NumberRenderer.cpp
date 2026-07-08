#include "NumberRenderer.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include <vector>

NumberRenderer::NumberRenderer(TTF_TextEngine *engine, TTF_Font *font) {
  if (engine && font) {
    for (size_t i = 0; i < nums_text_.size(); ++i) {
      const char *NUM_STR[] = {"0", "1", "2", "3", "4",
                               "5", "6", "7", "8", "9"};
      nums_text_[i].reset(TTF_CreateText(engine, font, NUM_STR[i], 1));
    }
  }
}

void NumberRenderer::render_num(int num, Point<float> pos) const {
  static constexpr auto FONT_SIZE = 32u;

  if (num < 10) { // Render the only digit
    TTF_DrawRendererText(nums_text_[num].get(), pos.x, pos.y);
  } else { // Render each individual digit
    std::vector<int> digits{};
    while (num > 0) {
      digits.push_back(num % 10);
      num /= 10;
    }
    while (!digits.empty()) {
      TTF_DrawRendererText(nums_text_[digits.back()].get(), pos.x, pos.y);
      digits.pop_back();
      pos.x += FONT_SIZE;
    }
  }
}
