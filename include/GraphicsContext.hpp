#pragma once
#include "EnumArray.hpp"
#include "Geometry.hpp"
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include <array>
#include <filesystem>

static constexpr float PIXEL_SCALE = 32.0f;

enum class GameText : size_t { Next, Hold, Score, Paused, GameOver, Count };

struct GraphicsContext {
  // Throws an SDL::Exception upon failure
  explicit GraphicsContext(const std::filesystem::path &atlas_texture_path,
                           const std::filesystem::path &font_path);

  void update_window_size();

  Size window_size{};
  SDL::Window window{};
  SDL::Renderer renderer{};
  SDL::Texture piece_atlas{};

  SDL::TTF::RendererTextEngine engine{};
  SDL::TTF::Font font{};
  EnumArray<SDL::TTF::Text, static_cast<size_t>(GameText::Count), GameText>
      game_text{};
  std::array<SDL::TTF::Text, 10> digit_text{};
};
