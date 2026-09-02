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

  void fit_context_within_window();

  void render_frame(const Tetris &tetris);

private:
  enum class BlockStyle : uint8_t { Solid, Ghost };

  void render_game_state(const Tetris &tetris);

  FSize win_size{};
  FPoint section_matrix{};
  FPoint section_left{};
  FPoint section_right{};

  SDL::Window window = nullptr;
  SDL::Renderer renderer = nullptr;
  SDL::Texture texture_atlas = nullptr;

  GameTextRenderer text_renderer;
};
