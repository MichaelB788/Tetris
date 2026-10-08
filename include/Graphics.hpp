#pragma once
#include "Piece.hpp"
#include "PlatformSDL.hpp"
#include "PlatformSDL_TTF.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include <array>
#include <filesystem>

class Tetris;

enum class GameText : size_t {
  Next = 0,
  Hold = 1,
  Score = 2,
  Paused = 3,
  GameOver = 4,
  Count // Sentinel value
};

enum class BlockStyle { Solid = 0, Ghost = 32 };

class Graphics {
public:
  struct Layout {
    FPoint matrix{};
    FPoint left{};
    FPoint right{};
  };

  struct TTF_Ctx {
    SDL::TTF::RendererTextEngine engine{};
    SDL::TTF::Font font{};
    std::array<SDL::TTF::Text, static_cast<size_t>(GameText::Count)>
        game_text_map{};
    std::array<SDL::TTF::Text, 10> uint_text_map{};
  };

  struct SDL_Ctx {
    SDL::Window window{};
    SDL::Renderer renderer{};
    SDL::Texture piece_atlas{};
  };

  Graphics(const std::filesystem::path &atlas_texture_path,
           const std::filesystem::path &font_path);

  void fit_context_within_window();

  void render_frame(const Tetris &tetris);

private:
  FSize window_size{};
  Layout layout{};
  SDL_Ctx sdl{};
  TTF_Ctx ttf{};
};

namespace graphics {
namespace sdl {
// Throws SDL::Exception on failure
void ctx_init(Graphics::SDL_Ctx &sdl,
              const std::filesystem::path &atlas_texture_path);

void draw_piece(Graphics::SDL_Ctx &sdl, Piece player, FPoint base,
                BlockStyle style);

void draw_matrix(Graphics::SDL_Ctx &sdl, const Matrix &matrix, FPoint base);
} // namespace sdl

namespace ttf {
// Throws SDL::Exception on failure
void ctx_init(Graphics::TTF_Ctx &ttf, SDL_Renderer &renderer,
              const std::filesystem::path &font_path);

void draw_uint(Graphics::TTF_Ctx &ttf, unsigned uint, FPoint pos);

void draw_text(Graphics::TTF_Ctx &ttf, GameText game_text, FPoint pos);

void draw_centered_text(Graphics::TTF_Ctx &ttf, GameText game_text,
                        FSize window_size);
} // namespace ttf
} // namespace graphics
