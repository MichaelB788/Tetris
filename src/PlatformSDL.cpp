#include "PlatformSDL.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

void WindowDestroyer::operator()(SDL_Window *window) const {
  SDL_DestroyWindow(window);
}

void RendererDestroyer::operator()(SDL_Renderer *renderer) const {
  SDL_DestroyRenderer(renderer);
}

void TextureDestroyer::operator()(SDL_Texture *texture) const {
  SDL_DestroyTexture(texture);
}

void SurfaceDestroyer::operator()(SDL_Surface *surface) const {
  SDL_DestroySurface(surface);
}

ExceptionSDL::ExceptionSDL(const std::string &msg_)
    : msg(msg_ + ": " + SDL_GetError()) {}

PlatformSDL::PlatformSDL() {
  if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    throw ExceptionSDL("Failed to initialize SDL video subsystem");
}

PlatformSDL::~PlatformSDL() { SDL_Quit(); }

PlatformSDL::Window PlatformSDL::create_window(const char *title, int w, int h,
                                               SDL_WindowFlags flags) const {
  SDL_Window *raw_window = SDL_CreateWindow(title, w, h, flags);
  if (!raw_window)
    throw ExceptionSDL("Failed to initialize the SDL window");

  return Window(raw_window);
}

PlatformSDL::Renderer PlatformSDL::create_renderer(Window &window) const {
  SDL_Renderer *raw_renderer = SDL_CreateRenderer(window.get(), NULL);
  if (!raw_renderer)
    throw ExceptionSDL("Failed to initialize the SDL renderer");

  return Renderer(raw_renderer);
}

PlatformSDL::Surface PlatformSDL::create_surface_from_img(
    const std::filesystem::path &path_to_img) const {
  if (!std::filesystem::exists(path_to_img))
    throw std::invalid_argument(
        std::string("Could not create SDL surface. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());

  SDL_Surface *raw_surface = IMG_Load(path_to_img.c_str());
  if (!raw_surface)
    throw ExceptionSDL("Could not load image to SDL surface");

  return Surface(raw_surface);
}

PlatformSDL::Texture
PlatformSDL::create_texture_from_surface(Renderer &renderer,
                                         Surface &surface) const {
  SDL_Texture *raw_texture =
      SDL_CreateTextureFromSurface(renderer.get(), surface.get());
  if (!raw_texture)
    throw ExceptionSDL("Could not create texture from surface");

  return Texture(raw_texture);
}

PlatformSDL::Texture PlatformSDL::create_texture_from_img(
    Renderer &renderer, const std::filesystem::path &path_to_img) const {
  if (!std::filesystem::exists(path_to_img))
    throw std::invalid_argument(
        std::string("Could not create SDL texture. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());

  SDL_Texture *raw_texture =
      IMG_LoadTexture(renderer.get(), path_to_img.c_str());
  if (!raw_texture)
    throw ExceptionSDL("Failed to create SDL texture from file");

  return Texture(raw_texture);
}
