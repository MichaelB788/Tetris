#include "PlatformSDL.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

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

void FontDestroyer::operator()(TTF_Font *font) const { TTF_CloseFont(font); }

void TextDestroyer::operator()(TTF_Text *text) const { TTF_DestroyText(text); }

void TextEngineDestroyer::operator()(TTF_TextEngine *engine) const {
  TTF_DestroyRendererTextEngine(engine);
}

ExceptionSDL::ExceptionSDL(const std::string &msg_)
    : msg(msg_ + ": " + SDL_GetError()) {}

PlatformSDL::PlatformSDL() {
  if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    throw ExceptionSDL("Failed to initialize the SDL video subsystem");
  if (!TTF_Init())
    throw ExceptionSDL("Failed to initialize SDL_TTF");
}

PlatformSDL::~PlatformSDL() {
  TTF_Quit();
  SDL_Quit();
}

PlatformSDL::Window PlatformSDL::create_window(const char *title, int w, int h,
                                               SDL_WindowFlags flags) {
  SDL_Window *raw_window = SDL_CreateWindow(title, w, h, flags);
  if (!raw_window)
    throw ExceptionSDL("Failed to initialize the SDL window");

  return Window(raw_window);
}

PlatformSDL::Renderer PlatformSDL::create_renderer(SDL_Window *window) {
  SDL_Renderer *raw_renderer = SDL_CreateRenderer(window, NULL);
  if (!raw_renderer)
    throw ExceptionSDL("Failed to initialize the SDL renderer");

  return Renderer(raw_renderer);
}

PlatformSDL::TextEngine
PlatformSDL::create_renderer_text_engine(SDL_Renderer *renderer) {
  TTF_TextEngine *raw_engine = TTF_CreateRendererTextEngine(renderer);
  if (!raw_engine)
    throw ExceptionSDL("Failed to create renderer text engine");

  return TextEngine(raw_engine);
}

PlatformSDL::Font
PlatformSDL::open_font(const std::filesystem::path &path_to_font,
                       float font_size) {
  TTF_Font *raw_font = TTF_OpenFont(path_to_font.c_str(), font_size);
  if (!raw_font)
    throw ExceptionSDL("Failed to open font");

  return Font(raw_font);
}

PlatformSDL::Surface
PlatformSDL::create_surface_from_img(const std::filesystem::path &path_to_img) {
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
PlatformSDL::create_texture_from_surface(SDL_Renderer *renderer,
                                         SDL_Surface *surface) {
  SDL_Texture *raw_texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!raw_texture)
    throw ExceptionSDL("Could not create texture from surface");

  return Texture(raw_texture);
}

PlatformSDL::Texture
PlatformSDL::create_texture_from_img(SDL_Renderer *renderer,
                                     const std::filesystem::path &path_to_img) {
  if (!std::filesystem::exists(path_to_img))
    throw std::invalid_argument(
        std::string("Could not create SDL texture. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());

  SDL_Texture *raw_texture = IMG_LoadTexture(renderer, path_to_img.c_str());
  if (!raw_texture)
    throw ExceptionSDL("Failed to create SDL texture from file");

  return Texture(raw_texture);
}

PlatformSDL::Text PlatformSDL::create_text(TTF_TextEngine *engine,
                                           TTF_Font *font, const char *str) {
  TTF_Text *raw_text = TTF_CreateText(engine, font, str, 0);
  if (!raw_text)
    throw ExceptionSDL("Failed to create TTF text");

  return Text(raw_text);
}
