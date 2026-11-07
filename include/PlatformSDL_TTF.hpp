#pragma once
#include <filesystem>
#include <memory>
#include <string_view>

struct SDL_Renderer;
struct TTF_TextEngine;
struct TTF_Text;
struct TTF_Font;

namespace SDL::TTF {
struct RendererTextEngineDestroyer {
  void operator()(TTF_TextEngine *engine) const;
};
struct FontCloser {
  void operator()(TTF_Font *font) const;
};
struct TextDestroyer {
  void operator()(TTF_Text *text) const;
};

using RendererTextEngine =
    std::unique_ptr<TTF_TextEngine, RendererTextEngineDestroyer>;
using Font = std::unique_ptr<TTF_Font, FontCloser>;
using Text = std::unique_ptr<TTF_Text, TextDestroyer>;

[[nodiscard]] auto create_renderer_text_engine(SDL_Renderer &renderer)
    -> RendererTextEngine;
[[nodiscard]] auto open_font(const std::filesystem::path &file, float ptsize)
    -> Font;
[[nodiscard]] auto create_text(TTF_TextEngine &engine, TTF_Font &font,
                               std::string_view text) -> Text;
} // namespace SDL::TTF
