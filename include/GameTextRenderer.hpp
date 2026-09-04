#pragma once
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <array>
#include <cstddef>
#include <filesystem>
#include <utility>

struct SDL_Renderer;

enum class TextIdx : size_t {
  Next = 0,
  Hold = 1,
  Score = 2,
  Paused = 3,
  GameOver = 4,
  Count // Sentiel value, not an actual text index
};

class GameTextRenderer {
public:
  GameTextRenderer() = default;

  GameTextRenderer(SDL_Renderer &renderer,
                   const std::filesystem::path &font_path);

  void draw_game_text(TextIdx i, FPoint pos);

  void draw_centered_game_text(TextIdx i, FSize window);

  void draw_unsigned_integer(unsigned n, FPoint pos) const;

private:
  SDL::TTF::RendererTextEngine engine = nullptr;
  SDL::TTF::Font font = nullptr;

  // Holds text objects representing predefined strings, indexable via TextIdx
  std::array<SDL::TTF::Text, std::to_underlying(TextIdx::Count)> text_map{};

  // Holds text objects representing single digits [0-9]
  std::array<SDL::TTF::Text, 10> nums_map{};
};
