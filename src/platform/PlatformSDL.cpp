#include "platform/PlatformSDL.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

sdl::Exception::Exception(const std::string &msg_)
    : msg(msg_ + ": " + SDL_GetError()) {}

void sdl::WindowDeleter::operator()(SDL_Window *window) {
  if (window)
    SDL_DestroyWindow(window);
}

void sdl::RendererDeleter::operator()(SDL_Renderer *renderer) {
  if (renderer)
    SDL_DestroyRenderer(renderer);
}

void sdl::SurfaceDeleter::operator()(SDL_Surface *surface) {
  if (surface)
    SDL_DestroySurface(surface);
}

void sdl::TextureDeleter::operator()(SDL_Texture *texture) {
  if (texture)
    SDL_DestroyTexture(texture);
}

auto sdl::create_window(const char *title, int w, int h, SDL_WindowFlags flags)
    -> Window {
  if (auto raw_window = SDL_CreateWindow(title, w, h, flags))
    return Window(raw_window);

  throw sdl::Exception("Failed to initialize the SDL window");
}

auto sdl::create_renderer(SDL_Window *window) -> Renderer {
  if (auto raw_renderer = SDL_CreateRenderer(window, nullptr))
    return Renderer(raw_renderer);

  throw sdl::Exception("Failed to initialize the SDL renderer");
}

auto sdl::create_texture_from_surface(SDL_Renderer *renderer,
                                      SDL_Surface *surface) -> Texture {
  if (auto raw_texture = SDL_CreateTextureFromSurface(renderer, surface))
    return Texture(raw_texture);

  throw sdl::Exception("Could not create texture from surface");
}
