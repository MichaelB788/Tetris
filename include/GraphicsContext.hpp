#pragma once
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include <array>
#include <filesystem>

static constexpr float PIXEL_SCALE = 32.0f;

struct GraphicsContext {
  struct GameText {
    SDL::TTF::Text next{}, held{}, score{}, paused{}, game_over{};
  };

  // Throws an SDL::Exception upon failure
  explicit GraphicsContext(const std::filesystem::path &atlas_texture_path,
                           const std::filesystem::path &font_path);

  SDL::Display display{};
  SDL::Texture piece_atlas{};

  SDL::TTF::RendererTextEngine engine{};
  SDL::TTF::Font font{};
  GameText game_text{};
  std::array<SDL::TTF::Text, 10> digit_text{};
};
