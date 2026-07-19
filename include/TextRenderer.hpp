#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <array>
#include <filesystem>

struct SDL_Renderer;

enum class Msg {
  Next = 0,
  Hold = 1,
  Score = 2,
  Paused = 3,
  GameOver = 4,
};

class TextRenderer {
public:
  TextRenderer(SDL_Renderer &renderer, const std::filesystem::path &font_path);

  void draw_text(Msg msg, Point<float> pos);
  void draw_num(unsigned num, Point<float> pos) const;

  [[nodiscard]] auto get_text_size(Msg msg) -> Size<float>;

private:
  struct TextEntry {
    SDL::TTF::Text texture;
  };

  SDL::TTF::RendererTextEngine engine = nullptr;
  SDL::TTF::Font font = nullptr;

  std::array<SDL::TTF::Text, 5> text_map{};
  std::array<SDL::TTF::Text, 10> nums_map{};
};
