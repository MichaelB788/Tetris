#include "PlatformSDL_TTF.hpp"
#include "PlatformSDL.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

void SDL::TTF::RendererTextEngineDestroyer::operator()(
    TTF_TextEngine *engine) const {
  TTF_DestroyRendererTextEngine(engine);
}

void SDL::TTF::FontCloser::operator()(TTF_Font *font) const {
  TTF_CloseFont(font);
}

void SDL::TTF::TextDestroyer::operator()(TTF_Text *text) const {
  TTF_DestroyText(text);
}

auto SDL::TTF::create_renderer_text_engine(SDL_Renderer &renderer)
    -> RendererTextEngine {
  if (auto *rte_ptr = TTF_CreateRendererTextEngine(&renderer))
    return RendererTextEngine{rte_ptr};
  throw SDL::Exception("Failed to create renderer text engine");
}

auto SDL::TTF::open_font(const std::filesystem::path &file, float ptsize)
    -> Font {
  if (auto *font_ptr = TTF_OpenFont(file.c_str(), ptsize))
    return Font{font_ptr};
  throw SDL::Exception(std::string{"Failed to open font at "} + file.string());
}

auto SDL::TTF::create_text(TTF_TextEngine &engine, TTF_Font &font,
                           std::string_view text) -> Text {
  if (auto *text_ptr = TTF_CreateText(&engine, &font, text.data(), text.size()))
    return Text{text_ptr};
  throw SDL::Exception("Failed to create text");
}
