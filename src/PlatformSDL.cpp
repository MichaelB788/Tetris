#include "PlatformSDL.hpp"
#include <SDL3/SDL.h>

void SDL::WindowDeleter::operator()(SDL_Window *window) const {
  SDL_DestroyWindow(window);
}

void SDL::RendererDeleter::operator()(SDL_Renderer *renderer) const {
  SDL_DestroyRenderer(renderer);
}

void SDL::SurfaceDeleter::operator()(SDL_Surface *surface) const {
  SDL_DestroySurface(surface);
}

void SDL::TextureDeleter::operator()(SDL_Texture *texture) const {
  SDL_DestroyTexture(texture);
}
