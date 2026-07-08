#pragma once
#include <memory>

struct TTF_TextEngine;
struct TTF_Text;
struct TTF_Font;

namespace SDL::TTF {
struct RendererTextEngineDeleter {
  void operator()(TTF_TextEngine *engine);
};

struct FontDeleter {
  void operator()(TTF_Font *font);
};

struct TextDeleter {
  void operator()(TTF_Text *text);
};

using RendererTextEngine =
    std::unique_ptr<TTF_TextEngine, RendererTextEngineDeleter>;

using Font = std::unique_ptr<TTF_Font, FontDeleter>;

using Text = std::unique_ptr<TTF_Text, TextDeleter>;
} // namespace SDL::TTF
