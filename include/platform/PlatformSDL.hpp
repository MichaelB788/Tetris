#pragma once
#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
using SDL_WindowFlags = unsigned long;

namespace sdl {
class Exception : std::exception {
public:
  explicit Exception(const std::string &msg_);

  [[nodiscard]] const char *what() const noexcept override {
    return msg.c_str();
  }

private:
  std::string msg;
};

struct WindowDeleter {
  void operator()(SDL_Window *window);
};

struct RendererDeleter {
  void operator()(SDL_Renderer *renderer);
};

struct SurfaceDeleter {
  void operator()(SDL_Surface *surface);
};

struct TextureDeleter {
  void operator()(SDL_Texture *texture);
};

using Window = std::unique_ptr<SDL_Window, WindowDeleter>;

using Renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;

using Texture = std::unique_ptr<SDL_Texture, TextureDeleter>;

using Surface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;

[[nodiscard]] auto create_window(const char *title, int w, int h,
                                 SDL_WindowFlags flags) -> Window;

[[nodiscard]] auto create_renderer(SDL_Window *window) -> Renderer;

[[nodiscard]] auto create_texture_from_surface(SDL_Renderer *renderer,
                                               SDL_Surface *surface) -> Texture;
} // namespace sdl
