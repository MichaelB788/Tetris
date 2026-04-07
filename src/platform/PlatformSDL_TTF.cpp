#include "platform/PlatformSDL_TTF.hpp"
#include <SDL3_ttf/SDL_ttf.h>

void sdl::ttf::RendererTextEngineDeleter::operator()(TTF_TextEngine *engine) {
  if (engine)
    TTF_DestroyRendererTextEngine(engine);
}

void sdl::ttf::FontDeleter::operator()(TTF_Font *font) {
  if (font)
    TTF_CloseFont(font);
}

void sdl::ttf::TextDeleter::operator()(TTF_Text *text) {
  if (text)
    TTF_DestroyText(text);
}

auto sdl::ttf::create_renderer_text_engine(SDL_Renderer *renderer)
    -> RendererTextEngine {
  if (auto raw_engine = TTF_CreateRendererTextEngine(renderer))
    return RendererTextEngine(raw_engine);

  throw sdl::Exception("Failed to create renderer text engine");
}

auto sdl::ttf::open_font(const std::filesystem::path &path_to_font,
                         float font_size) -> Font {
  if (auto raw_font = TTF_OpenFont(path_to_font.c_str(), font_size))
    return Font(raw_font);

  throw sdl::Exception("Failed to open font");
}

auto sdl::ttf::create_text(TTF_TextEngine *engine, TTF_Font *font,
                           const char *str) -> Text {
  if (auto raw_text = TTF_CreateText(engine, font, str, 0))
    return Text(raw_text);

  throw sdl::Exception("Failed to create TTF text");
}
