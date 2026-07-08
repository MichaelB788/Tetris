#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include <array>
#include <filesystem>
#include <unordered_map>

class TextRenderer {
public:
  explicit TextRenderer(SDL_Renderer &renderer,
                        const std::filesystem::path &font_path,
                        float font_size);

  void render_text(std::string_view str, Point<float> pos);

  void render_int(int num, Point<float> pos) const;

private:
  float font_size_{};
  SDL::TTF::RendererTextEngine text_engine_{};
  SDL::TTF::Font font_{};

  std::array<SDL::TTF::Text, 10> nums_text_{};
  std::unordered_map<std::string_view, SDL::TTF::Text> cached_text_{};
};
