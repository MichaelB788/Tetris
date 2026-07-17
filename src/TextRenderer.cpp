#include "TextRenderer.hpp"
#include "Constants.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <utility>

TextRenderer::TextRenderer(SDL_Renderer &renderer,
                           const std::filesystem::path &font_path)
    : engine_(TTF_CreateRendererTextEngine(&renderer)),
      font_(TTF_OpenFont(font_path.c_str(), FONT_SCALE)) {
  if (!engine_) {
    throw std::runtime_error("Couldn't create text engine");
  } else if (!font_) {
    throw std::runtime_error("Couldn't create text engine");
  }

  const std::array nums_str{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < nums_.size(); ++i) {
    nums_[i].reset(TTF_CreateText(engine_.get(), font_.get(), nums_str[i], 1));
  }
}

void TextRenderer::draw_text(std::string_view str, Point<float> pos) {
  TTF_DrawRendererText(&find_text(str), pos.x, pos.y);
}

void TextRenderer::draw_num(unsigned num, Point<float> pos) const {
  if (num < 10) {
    TTF_DrawRendererText(nums_[num].get(), pos.x, pos.y);
    return;
  }
  std::vector<unsigned> digits{};
  while (num > 0) {
    digits.push_back(num % 10);
    num /= 10;
  }
  while (!digits.empty()) {
    TTF_DrawRendererText(nums_[digits.back()].get(), pos.x, pos.y);
    digits.pop_back();
    pos.x += FONT_SCALE;
  }
}

auto TextRenderer::get_text_size(std::string_view str) -> std::pair<int, int> {
  std::pair<int, int> dim;
  TTF_GetTextSize(&find_text(str), &dim.first, &dim.second);
  return dim;
}

auto TextRenderer::find_text(std::string_view str) -> TTF_Text & {
  size_t i = 0;
  for (; i < text_.size(); ++i) {
    if (text_[i].str == str)
      break;
  }

  if (i == text_.size()) {
    text_.push_back({.str = str,
                     .texture{TTF_CreateText(engine_.get(), font_.get(),
                                             str.data(), str.size())}});
  }

  return *text_[i].texture;
}
