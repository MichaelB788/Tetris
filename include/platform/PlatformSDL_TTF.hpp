#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

struct RendererTextEngineDeleter {
  void operator()(TTF_TextEngine *engine) {
    TTF_DestroyRendererTextEngine(engine);
  }
};
struct FontDeleter {
  void operator()(TTF_Font *font) { TTF_CloseFont(font); }
};
struct TextDeleter {
  void operator()(TTF_Text *text) { TTF_DestroyText(text); }
};

using RendererTextEngine =
    std::unique_ptr<TTF_TextEngine, RendererTextEngineDeleter>;
using Font = std::unique_ptr<TTF_Font, FontDeleter>;
using Text = std::unique_ptr<TTF_Text, TextDeleter>;
