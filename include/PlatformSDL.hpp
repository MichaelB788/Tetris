#ifndef PLATFORM_SDL_HPP
#define PLATFORM_SDL_HPP
#include <filesystem>
#include <memory>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
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

struct PlatformSDL {
  using Window = std::unique_ptr<SDL_Window, WindowDestroyer>;
  using Renderer = std::unique_ptr<SDL_Renderer, RendererDestroyer>;
  using Texture = std::unique_ptr<SDL_Texture, TextureDestroyer>;
  using Surface = std::unique_ptr<SDL_Surface, SurfaceDestroyer>;

  PlatformSDL();

  ~PlatformSDL();

  Window create_window(const char *title, int w, int h,
                       SDL_WindowFlags flags) const;

  Renderer create_renderer(Window &window) const;

  Surface
  create_surface_from_img(const std::filesystem::path &path_to_img) const;

  Texture create_texture_from_surface(Renderer &renderer,
                                      Surface &surface) const;

  Texture
  create_texture_from_img(Renderer &renderer,
                          const std::filesystem::path &path_to_img) const;
};

#endif
