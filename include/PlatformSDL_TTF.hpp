#pragma once
#include <filesystem>
#include <memory>
#include <string_view>

struct SDL_Renderer;
struct TTF_TextEngine;
struct TTF_Text;
struct TTF_Font;

namespace SDL::TTF {
struct RendererTextEngineDeleter {
  void operator()(TTF_TextEngine *engine) const;
};
struct FontDeleter {
  void operator()(TTF_Font *font) const;
};
struct TextDeleter {
  void operator()(TTF_Text *text) const;
};

using RendererTextEngine =
    std::unique_ptr<TTF_TextEngine, RendererTextEngineDeleter>;
using Font = std::unique_ptr<TTF_Font, FontDeleter>;
using Text = std::unique_ptr<TTF_Text, TextDeleter>;

[[nodiscard]] auto create_renderer_text_engine(SDL_Renderer &renderer)
    -> RendererTextEngine;
[[nodiscard]] auto open_font(const std::filesystem::path &file, float ptsize)
    -> Font;
[[nodiscard]] auto create_text(TTF_TextEngine &engine, TTF_Font &font,
                               std::string_view text) -> Text;
} // namespace SDL::TTF
