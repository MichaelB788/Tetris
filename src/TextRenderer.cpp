#include "TextRenderer.hpp"
#include "Constants.hpp"
#include "Size.hpp"
#include <SDL3_ttf/SDL_ttf.h>

TextRenderer::TextRenderer(SDL_Renderer &renderer,
                           const std::filesystem::path &font_path)
    : engine(TTF_CreateRendererTextEngine(&renderer)),
      font(TTF_OpenFont(font_path.c_str(), FONT_SCALE)) {
  if (!engine) {
    throw std::runtime_error("Couldn't create text engine");
  } else if (!font) {
    throw std::runtime_error("Couldn't create font");
  }

  const std::array nums_str{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < nums_map.size(); ++i) {
    nums_map[i].reset(TTF_CreateText(engine.get(), font.get(), nums_str[i], 1));
  }
}

void TextRenderer::draw_text(std::string_view str, Point<float> pos) {
  TTF_DrawRendererText(&find_text(str), pos.x, pos.y);
}

void TextRenderer::draw_num(unsigned num, Point<float> pos) const {
  if (num < 10) {
    TTF_DrawRendererText(nums_map[num].get(), pos.x, pos.y);
    return;
  }
  std::vector<unsigned> digits{};
  while (num > 0) {
    digits.push_back(num % 10);
    num /= 10;
  }
  while (!digits.empty()) {
    TTF_DrawRendererText(nums_map[digits.back()].get(), pos.x, pos.y);
    digits.pop_back();
    pos.x += FONT_SCALE;
  }
}

auto TextRenderer::get_text_size(std::string_view str) -> Size<float> {
  int w, h;
  TTF_GetTextSize(&find_text(str), &w, &h);
  return {.w = static_cast<float>(w), .h = static_cast<float>(h)};
}

auto TextRenderer::find_text(std::string_view str) -> TTF_Text & {
  for (auto &[key, texture] : text_map) {
    if (key == str) {
      return *texture;
    }
  }

  text_map.push_back({.key = str,
                      .texture{TTF_CreateText(engine.get(), font.get(),
                                              str.data(), str.size())}});
  return *text_map.back().texture;
}
