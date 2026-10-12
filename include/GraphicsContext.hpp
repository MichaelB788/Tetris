#pragma once
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include <array>
#include <filesystem>

static constexpr float PIXL_SZ = 32;

enum class GameText : size_t {
  Next = 0,
  Hold = 1,
  Score = 2,
  Paused = 3,
  GameOver = 4,
  Count // Sentinel value
};

struct GraphicsContext {
  // Throws an SDL::Exception upon failure
  explicit GraphicsContext(const std::filesystem::path &atlas_texture_path,
                           const std::filesystem::path &font_path);

  SDL::Window window{};
  SDL::Renderer renderer{};
  SDL::Texture piece_atlas{};
  SDL::TTF::RendererTextEngine engine{};
  SDL::TTF::Font font{};
  std::array<SDL::TTF::Text, static_cast<size_t>(GameText::Count)>
      game_text_map{};
  std::array<SDL::TTF::Text, 10> uint_text_map{};
};
