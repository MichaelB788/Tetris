#pragma once
#include "PlatformSDL.hpp"
#include <SDL3/SDL.h>

void SDL::WindowDeleter::operator()(SDL_Window *window) {
  SDL_DestroyWindow(window);
}

void SDL::RendererDeleter::operator()(SDL_Renderer *renderer) {
  SDL_DestroyRenderer(renderer);
}

void SDL::SurfaceDeleter::operator()(SDL_Surface *surface) {
  SDL_DestroySurface(surface);
}

void SDL::TextureDeleter::operator()(SDL_Texture *texture) {
  SDL_DestroyTexture(texture);
}
