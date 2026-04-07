#pragma once
#include "platform/PlatformSDL.hpp"
#include <filesystem>

struct TTF_TextEngine;
struct TTF_Text;
struct TTF_Font;

namespace sdl::ttf {
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

[[nodiscard]] auto create_renderer_text_engine(SDL_Renderer *renderer)
    -> RendererTextEngine;

[[nodiscard]] auto open_font(const std::filesystem::path &path_to_font,
                             float font_size) -> Font;

[[nodiscard]] auto create_text(TTF_TextEngine *engine, TTF_Font *font,
                               const char *str) -> Text;
} // namespace sdl::ttf
