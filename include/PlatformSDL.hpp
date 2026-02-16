#ifndef PLATFORM_SDL_HPP
#define PLATFORM_SDL_HPP
#include <filesystem>
#include <memory>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
using SDL_WindowFlags = unsigned long;

class ExceptionSDL : std::exception {
public:
  ExceptionSDL(const std::string &msg_);
  const char *what() const noexcept override { return msg.c_str(); }

private:
  std::string msg;
};

struct PlatformSDL {
  using Window = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>;
  using Renderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>;
  using Texture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>;
  using Surface = std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>;

  PlatformSDL();

  ~PlatformSDL();

  Window create_window(const char *title, int w, int h,
                       SDL_WindowFlags flags) const;

  Renderer create_renderer(Window &window) const;

  Surface
  create_surface_from_img(const std::filesystem::path &path_to_img) const;

  Texture create_texture_from_surface(Renderer &renderer,
                                      Surface &surface) const;

  Texture
  create_texture_from_img(Renderer &renderer,
                          const std::filesystem::path &path_to_img) const;
};

#endif
