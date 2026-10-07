#pragma once
#include <exception>
#include <memory>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace SDL {
struct WindowDeleter {
  void operator()(SDL_Window *window) const;
};

struct RendererDeleter {
  void operator()(SDL_Renderer *renderer) const;
};

struct SurfaceDeleter {
  void operator()(SDL_Surface *surface) const;
};

struct TextureDeleter {
  void operator()(SDL_Texture *texture) const;
};

class Exception : public std::exception {
public:
  Exception(std::string &msg);
  Exception(const char *msg);
  [[nodiscard]] auto what() const noexcept -> const char * override;

private:
  std::string msg;
};

using Window = std::unique_ptr<SDL_Window, WindowDeleter>;
using Renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;
using Texture = std::unique_ptr<SDL_Texture, TextureDeleter>;
using Surface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;
} // namespace SDL
