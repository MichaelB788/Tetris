#pragma once
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace SDL {
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
} // namespace SDL
