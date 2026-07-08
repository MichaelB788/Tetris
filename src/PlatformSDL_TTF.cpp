#include "PlatformSDL_TTF.hpp"
#include <SDL3_ttf/SDL_ttf.h>

void SDL::TTF::RendererTextEngineDeleter::operator()(TTF_TextEngine *engine) {
  TTF_DestroyRendererTextEngine(engine);
}

void SDL::TTF::FontDeleter::operator()(TTF_Font *font) { TTF_CloseFont(font); }

void SDL::TTF::TextDeleter::operator()(TTF_Text *text) {
  TTF_DestroyText(text);
}
