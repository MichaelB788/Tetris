#pragma once
#include <SDL3/SDL.h>
#include <exception>
#include <memory>
#include <string>

namespace SDL {
class Error final : public std::exception {
public:
  Error(const char *message)
      : msg(std::string(message) + ": " + SDL_GetError()) {}

  const char *what() const noexcept override { return msg.c_str(); };

private:
  std::string msg;
};

struct WindowDeleter {
  void operator()(SDL_Window *window) { SDL_DestroyWindow(window); }
};
struct RendererDeleter {
  void operator()(SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); }
};
struct SurfaceDeleter {
  void operator()(SDL_Surface *surface) { SDL_DestroySurface(surface); }
};
struct TextureDeleter {
  void operator()(SDL_Texture *texture) { SDL_DestroyTexture(texture); }
};

using Window = std::unique_ptr<SDL_Window, WindowDeleter>;
using Renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;
using Texture = std::unique_ptr<SDL_Texture, TextureDeleter>;
using Surface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;
} // namespace SDL
