#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <memory>

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
