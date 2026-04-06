#include "platform/PlatformSDL.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

auto sdl::create_window(const char *title, int w, int h, SDL_WindowFlags flags)
    -> Window {
  if (auto raw_window = SDL_CreateWindow(title, w, h, flags))
    return Window(raw_window);

  throw Exception("Failed to initialize the SDL window");
}

auto sdl::create_renderer(SDL_Window *window) -> Renderer {
  if (auto raw_renderer = SDL_CreateRenderer(window, nullptr))
    return Renderer(raw_renderer);

  throw Exception("Failed to initialize the SDL renderer");
}

auto sdl::create_texture_from_surface(SDL_Renderer *renderer,
                                      SDL_Surface *surface) -> Texture {
  if (auto raw_texture = SDL_CreateTextureFromSurface(renderer, surface))
    return Texture(raw_texture);

  throw Exception("Could not create texture from surface");
}

auto sdl::img::create_surface_from_img(const fs::path &path_to_img) -> Surface {
  if (!fs::exists(path_to_img)) {
    throw std::invalid_argument(
        std::string("Could not create SDL surface. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());
  }

  if (auto raw_surface = IMG_Load(path_to_img.c_str()))
    return Surface(raw_surface);

  throw Exception("Could not load image to SDL surface");
}

auto sdl::img::create_texture_from_img(SDL_Renderer *renderer,
                                       const fs::path &path_to_img) -> Texture {
  if (!fs::exists(path_to_img)) {
    throw std::invalid_argument(
        std::string("Could not create SDL texture. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());
  }

  if (auto raw_texture = IMG_LoadTexture(renderer, path_to_img.c_str()))
    return Texture(raw_texture);

  throw Exception("Failed to create SDL texture from file");
}

auto sdl::ttf::create_renderer_text_engine(SDL_Renderer *renderer)
    -> RendererTextEngine {
  if (auto raw_engine = TTF_CreateRendererTextEngine(renderer))
    return RendererTextEngine(raw_engine);

  throw Exception("Failed to create renderer text engine");
}

auto sdl::ttf::open_font(const std::filesystem::path &path_to_font,
                         float font_size) -> Font {
  if (auto raw_font = TTF_OpenFont(path_to_font.c_str(), font_size))
    return Font(raw_font);

  throw Exception("Failed to open font");
}

auto sdl::ttf::create_text(TTF_TextEngine *engine, TTF_Font *font,
                           const char *str) -> Text {
  if (auto raw_text = TTF_CreateText(engine, font, str, 0))
    return Text(raw_text);

  throw Exception("Failed to create TTF text");
}
