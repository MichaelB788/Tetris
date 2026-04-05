#pragma once
#include <filesystem>
#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

class ExceptionSDL : std::exception {
public:
  ExceptionSDL(const std::string &msg_);
  const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

namespace sdl {
using SDL_WindowFlags = unsigned long;
using Window = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
using Renderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
using Texture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>;
using Surface = std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>;

[[nodiscard]] auto create_window(const char *title, int w, int h,
                                 SDL_WindowFlags flags) -> Window;

[[nodiscard]] auto create_renderer(SDL_Window &window) -> Renderer;

[[nodiscard]] auto create_texture_from_surface(SDL_Renderer &renderer,
                                               SDL_Surface &surface) -> Texture;
} // namespace sdl

namespace sdl::img {
namespace fs = std::filesystem;

[[nodiscard]] auto create_surface_from_img(const fs::path &path_to_img)
    -> Surface;

[[nodiscard]] auto create_texture_from_img(SDL_Renderer &renderer,
                                           const fs::path &path_to_img)
    -> Texture;
} // namespace sdl::img

struct TTF_TextEngine;
struct TTF_Font;
struct TTF_Text;

namespace sdl::ttf {
namespace fs = std::filesystem;
using TextEngine = std::unique_ptr<TTF_TextEngine, void (*)(TTF_TextEngine *)>;
using Font = std::unique_ptr<TTF_Font, void (*)(TTF_Font *)>;
using Text = std::unique_ptr<TTF_Text, void (*)(TTF_Text *)>;

[[nodiscard]] auto create_renderer_text_engine(SDL_Renderer &renderer)
    -> TextEngine;

[[nodiscard]] auto open_font(const fs::path &path_to_font, float font_size)
    -> Font;

[[nodiscard]] auto create_text(TTF_TextEngine &engine, TTF_Font &font,
                               const char *str) -> Text;
} // namespace sdl::ttf
