#pragma once
#include <filesystem>
#include <memory>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
class TTF_TextEngine;
class TTF_Font;
class TTF_Text;

using SDL_WindowFlags = unsigned long;

class ExceptionSDL : std::exception {
public:
  ExceptionSDL(const std::string &msg_);
  const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

struct WindowDestroyer {
  void operator()(SDL_Window *window) const;
};

struct RendererDestroyer {
  void operator()(SDL_Renderer *renderer) const;
};

struct TextureDestroyer {
  void operator()(SDL_Texture *texture) const;
};

struct SurfaceDestroyer {
  void operator()(SDL_Surface *surface) const;
};

struct FontDestroyer {
  void operator()(TTF_Font *font) const;
};

struct TextDestroyer {
  void operator()(TTF_Text *text) const;
};

struct TextEngineDestroyer {
  void operator()(TTF_TextEngine *engine) const;
};

struct PlatformSDL {
  using Window = std::unique_ptr<SDL_Window, WindowDestroyer>;
  using Renderer = std::unique_ptr<SDL_Renderer, RendererDestroyer>;
  using TextEngine = std::unique_ptr<TTF_TextEngine, TextEngineDestroyer>;
  using Texture = std::unique_ptr<SDL_Texture, TextureDestroyer>;
  using Surface = std::unique_ptr<SDL_Surface, SurfaceDestroyer>;
  using Font = std::unique_ptr<TTF_Font, FontDestroyer>;
  using Text = std::unique_ptr<TTF_Text, TextDestroyer>;

  PlatformSDL();

  ~PlatformSDL();

  static Window create_window(const std::string &title, int w, int h,
                              SDL_WindowFlags flags);

  static Renderer create_renderer(SDL_Window &window);

  static TextEngine create_renderer_text_engine(SDL_Renderer &renderer);

  static Font open_font(const std::filesystem::path &path_to_font,
                        float font_size);

  static Surface
  create_surface_from_img(const std::filesystem::path &path_to_img);

  static Texture create_texture_from_surface(SDL_Renderer &renderer,
                                             SDL_Surface &surface);

  static Texture
  create_texture_from_img(SDL_Renderer &renderer,
                          const std::filesystem::path &path_to_img);

  static Text create_text(TTF_TextEngine &engine, TTF_Font &font,
                          const std::string &str);
};
