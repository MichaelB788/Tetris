#include "GraphicsContext.hpp"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

GraphicsContext::GraphicsContext(
    const std::filesystem::path &atlas_texture_path,
    const std::filesystem::path &font_path) {
  if (window.reset(SDL_CreateWindow("Tetris", 900, 1000, SDL_WINDOW_RESIZABLE));
      window == nullptr)
    throw SDL::Exception("SDL_CreateWindow");

  if (renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
      renderer == nullptr)
    throw SDL::Exception("SDL_CreateRenderer");

  if (piece_atlas.reset(
          IMG_LoadTexture(renderer.get(), atlas_texture_path.c_str()));
      piece_atlas == nullptr)
    throw SDL::Exception("IMG_LoadTexture");

  if (engine.reset(TTF_CreateRendererTextEngine(renderer.get()));
      engine == nullptr)
    throw SDL::Exception("TTF_CreateRendererTextEngine");

  if (font.reset(TTF_OpenFont(font_path.c_str(), PIXL_SZ)); font == nullptr)
    throw SDL::Exception("TTF_OpenFont");

  static constexpr std::array text_str{"NEXT", "HOLD", "SCORE", "PAUSED",
                                       "GAMEOVER!\n"
                                       "\n"
                                       "CONTINUE?\n"
                                       "\n"
                                       "[Y/N]"};
  for (size_t i = 0; i < game_text_map.size(); ++i) {
    if (game_text_map[i].reset(
            TTF_CreateText(engine.get(), font.get(), text_str[i], 0));
        game_text_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText (game text)");
  }

  static constexpr std::array nums_str{'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};
  for (size_t i = 0; i < uint_text_map.size(); ++i) {
    if (uint_text_map[i].reset(
            TTF_CreateText(engine.get(), font.get(), &nums_str[i], 1));
        uint_text_map[i] == nullptr)
      throw SDL::Exception("TTF_CreateText (uint text)");
  }
}
