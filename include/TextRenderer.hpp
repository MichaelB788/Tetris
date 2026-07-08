#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include <array>
#include <cstddef>
#include <filesystem>
#include <string_view>
#include <vector>

class TextRenderer {
public:
  explicit TextRenderer(SDL_Renderer &renderer,
                        const std::filesystem::path &font_path);

  void render_text(std::string_view str, Point<float> pos);

  void render_int(int num, Point<float> pos) const;

private:
  auto index_of_text(std::string_view str) const -> size_t;

  struct TextEntry {
    std::string_view str;
    SDL::TTF::Text texture;
  };

  SDL::TTF::RendererTextEngine text_engine_{};
  SDL::TTF::Font font_{};
  std::array<SDL::TTF::Text, 10> nums_text_{};
  std::vector<TextEntry> text_map_{};
};
