#pragma once
#include "GameTextRenderer.hpp"
#include "PlatformSDL.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <cstdint>
#include <filesystem>

class Tetris;
class Matrix;

class RenderingModule {
public:
  RenderingModule(const std::filesystem::path &atlas_path,
                  const std::filesystem::path &font_path);

  void update_window_size();

  void render_frame(const Tetris &tetris);

private:
  enum class BlockStyle : uint8_t { Solid, Ghost };

  void render_game_state(const Tetris &tetris);

  Size<float> win_size{};
  Point<float> section_matrix{};
  Point<float> section_left{};
  Point<float> section_right{};

  SDL::Window window = nullptr;
  SDL::Renderer renderer = nullptr;
  SDL::Texture texture_atlas = nullptr;

  GameTextRenderer text_renderer;
};
