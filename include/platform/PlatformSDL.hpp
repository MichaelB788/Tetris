#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <memory>
#include <string>

namespace sdl {
class Exception : std::exception {
public:
  explicit Exception(const std::string &msg_): msg(msg_ + ": " + SDL_GetError()) {}

  [[nodiscard]] const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

using Window = std::unique_ptr<SDL_Window, decltype([](SDL_Window *window) {
                                 if (window)
                                   SDL_DestroyWindow(window);
                               })>;

using Renderer =
    std::unique_ptr<SDL_Renderer, decltype([](SDL_Renderer *renderer) {
                      if (renderer)
                        SDL_DestroyRenderer(renderer);
                    })>;

using Texture = std::unique_ptr<SDL_Texture, decltype([](SDL_Texture *texture) {
                                  if (texture)
                                    SDL_DestroyTexture(texture);
                                })>;

using Surface = std::unique_ptr<SDL_Surface, decltype([](SDL_Surface *surface) {
                                  if (surface)
                                    SDL_DestroySurface(surface);
                                })>;

[[nodiscard]] auto create_window(const char *title, int w, int h,
                                 SDL_WindowFlags flags) -> Window;

[[nodiscard]] auto create_renderer(SDL_Window *window) -> Renderer;

[[nodiscard]] auto create_texture_from_surface(SDL_Renderer *renderer,
                                               SDL_Surface *surface) -> Texture;
} // namespace sdl

namespace sdl::img {
namespace fs = std::filesystem;

[[nodiscard]] auto create_surface_from_img(const fs::path &path_to_img)
    -> Surface;

[[nodiscard]] auto create_texture_from_img(SDL_Renderer *renderer,
                                           const fs::path &path_to_img)
    -> Texture;
} // namespace sdl::img

namespace sdl::ttf {
namespace fs = std::filesystem;
using RendererTextEngine =
    std::unique_ptr<TTF_TextEngine, decltype([](TTF_TextEngine *engine) {
                      if (engine)
                        TTF_DestroyRendererTextEngine(engine);
                    })>;

using Font = std::unique_ptr<TTF_Font, decltype([](TTF_Font *font) {
                               if (font)
                                 TTF_CloseFont(font);
                             })>;

using Text = std::unique_ptr<TTF_Text, decltype([](TTF_Text *text) {
                               if (text)
                                 TTF_DestroyText(text);
                             })>;

[[nodiscard]] auto create_renderer_text_engine(SDL_Renderer *renderer)
    -> RendererTextEngine;

[[nodiscard]] auto open_font(const fs::path &path_to_font, float font_size)
    -> Font;

[[nodiscard]] auto create_text(TTF_TextEngine *engine, TTF_Font *font,
                               const char *str) -> Text;
} // namespace sdl::ttf
