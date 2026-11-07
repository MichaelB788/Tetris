#include "PlatformSDL.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <string>

void SDL::WindowDeleter::operator()(SDL_Window *window) const {
  SDL_DestroyWindow(window);
}

void SDL::RendererDeleter::operator()(SDL_Renderer *renderer) const {
  SDL_DestroyRenderer(renderer);
}

void SDL::TextureDeleter::operator()(SDL_Texture *texture) const {
  SDL_DestroyTexture(texture);
}

SDL::Exception::Exception(std::string &msg)
    : msg{msg + ": " + SDL_GetError()} {}

SDL::Exception::Exception(std::string_view msg)
    : msg{std::string{msg} + ": " + SDL_GetError()} {}

auto SDL::Exception::what() const noexcept -> const char * {
  return msg.data();
}

SDL::Display::Display(std::string_view name, int w, int h,
                      SDL_WindowFlags flags)
    : w(w), h(h), window{create_window(name.data(), w, h, flags)},
      renderer(create_renderer(*window, {})) {}

void SDL::Display::window_resized() { SDL_GetWindowSize(window.get(), &w, &h); }

auto SDL::create_window(std::string_view name, int w, int h,
                        SDL_WindowFlags flags) -> Window {
  if (auto *window_ptr = SDL_CreateWindow(name.data(), w, h, flags))
    return Window{window_ptr};
  throw SDL::Exception("Failed to create window");
}

auto SDL::create_renderer(SDL_Window &window, std::string_view name)
    -> Renderer {
  if (auto *renderer_ptr = SDL_CreateRenderer(&window, name.data()))
    return Renderer{renderer_ptr};
  throw SDL::Exception("Failed to create renderer");
}

auto SDL::load_texture_from_image(SDL_Renderer &renderer,
                                  const std::filesystem::path &file)
    -> Texture {
  if (auto *img_ptr = IMG_LoadTexture(&renderer, file.c_str()))
    return Texture{img_ptr};
  throw SDL::Exception("Failed to load image");
}
