#include "PlatformSDL_TTF.hpp"
#include <SDL3_ttf/SDL_ttf.h>

void SDL::TTF::RendererTextEngineDeleter::operator()(TTF_TextEngine *engine) const {
  TTF_DestroyRendererTextEngine(engine);
}

void SDL::TTF::FontDeleter::operator()(TTF_Font *font) const { TTF_CloseFont(font); }

void SDL::TTF::TextDeleter::operator()(TTF_Text *text) const {
  TTF_DestroyText(text);
}
