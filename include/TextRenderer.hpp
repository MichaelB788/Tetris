#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <array>
#include <filesystem>
#include <string_view>
#include <vector>

struct SDL_Renderer;

class TextRenderer {
public:
  TextRenderer(SDL_Renderer &renderer, const std::filesystem::path &font_path);

  void draw_text(std::string_view str, Point<float> pos);
  void draw_num(unsigned num, Point<float> pos) const;

  [[nodiscard]] auto get_text_size(std::string_view str) -> Size<float>;

private:
  struct TextEntry {
    std::string_view str;
    SDL::TTF::Text texture;
  };

  [[nodiscard]] auto find_text(std::string_view str) -> TTF_Text &;

  SDL::TTF::RendererTextEngine engine = nullptr;
  SDL::TTF::Font font = nullptr;

  std::vector<TextEntry> text{};
  std::array<SDL::TTF::Text, 10> nums{};
};
