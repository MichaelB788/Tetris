#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include <string_view>
#include <vector>

class TextRenderer {
public:
  void render_text(std::string_view str, Point<float> pos,
                   TTF_TextEngine &engine, TTF_Font &font);

private:
  auto index_of_text(std::string_view str) const -> size_t;

  struct TextEntry {
    std::string_view str;
    SDL::TTF::Text texture;
  };

  std::vector<TextEntry> text_map_{};
};
