#include "TextRenderer.hpp"

void TextRenderer::render_text(std::string_view str, Point<float> pos,
                               TTF_TextEngine &engine, TTF_Font &font) {
  const auto i = index_of_text(str);
  if (i == text_map_.size()) {
    text_map_.push_back(TextEntry{
        .str = str,
        .texture{TTF_CreateText(&engine, &font, str.data(), str.size())}});
  }
  TTF_DrawRendererText(text_map_[i].texture.get(), pos.x, pos.y);
}

auto TextRenderer::index_of_text(std::string_view str) const -> size_t {
  size_t i = 0;
  for (; i < text_map_.size(); ++i) {
    if (text_map_[i].str == str) {
      return i;
    }
  }
  return i;
}
