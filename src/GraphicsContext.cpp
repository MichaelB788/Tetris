#include "GraphicsContext.hpp"
#include "PlatformSDL_TTF.hpp"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string_view>

GraphicsContext::GraphicsContext(
    const std::filesystem::path &atlas_texture_path,
    const std::filesystem::path &font_path)
    : window_size{900, 1000},
      window(SDL::create_window("Tetris", window_size.w, window_size.h,
                                SDL_WINDOW_RESIZABLE)),
      renderer(SDL::create_renderer(*window, {})),
      piece_atlas(SDL::load_texture_from_image(*renderer, atlas_texture_path)),
      engine(SDL::TTF::create_renderer_text_engine(*renderer)),
      font(SDL::TTF::open_font(font_path, PIXEL_SCALE)) {
  auto make_text = [this](std::string_view text) {
    return SDL::TTF::create_text(*engine, *font, text);
  };

  game_text.next = make_text("NEXT");
  game_text.held = make_text("HELD");
  game_text.score = make_text("SCORE");
  game_text.paused = make_text("PAUSED");
  game_text.game_over = make_text("GAME OVER!\n\nCONTINUE?\n\n[Y/N]");

  static constexpr std::array nums_str{"0", "1", "2", "3", "4",
                                       "5", "6", "7", "8", "9"};
  for (size_t i = 0; i < digit_text.size(); ++i) {
    digit_text[i] = make_text(nums_str[i]);
  }
};

void GraphicsContext::update_window_size() {
  SDL_GetWindowSize(window.get(), &window_size.w, &window_size.h);
}
