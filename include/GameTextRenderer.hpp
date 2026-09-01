#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <array>
#include <cstddef>
#include <filesystem>

struct SDL_Renderer;

enum class GameText : size_t { Next, Hold, Score, Paused, GameOver };

class GameTextRenderer {
public:
  GameTextRenderer(SDL_Renderer &renderer,
                   const std::filesystem::path &font_path);

  void draw_game_text(GameText txt, Point<float> pos);

  void draw_centered_game_text(GameText txt, Size<float> window);

  void draw_unsigned_integer(unsigned n, Point<float> pos) const;

private:
  SDL::TTF::RendererTextEngine engine = nullptr;
  SDL::TTF::Font font = nullptr;

  std::array<SDL::TTF::Text, 5> text_map{};
  std::array<SDL::TTF::Text, 10> nums_map{};
};
