#pragma once
#include <SDL3/SDL_video.h>
#include <exception>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>

struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

namespace SDL {
struct WindowDestroyer {
  void operator()(SDL_Window *window) const;
};

struct RendererDestroyer {
  void operator()(SDL_Renderer *renderer) const;
};

struct TextureDestroyer {
  void operator()(SDL_Texture *texture) const;
};

class Exception : public std::exception {
public:
  Exception(std::string &msg);
  Exception(std::string_view msg);
  [[nodiscard]] auto what() const noexcept -> const char * override;

private:
  std::string msg;
};

using Window = std::unique_ptr<SDL_Window, WindowDestroyer>;
using Renderer = std::unique_ptr<SDL_Renderer, RendererDestroyer>;
using Texture = std::unique_ptr<SDL_Texture, TextureDestroyer>;

[[nodiscard]] auto create_window(std::string_view name, int w, int h,
                                 SDL_WindowFlags flags) -> Window;
[[nodiscard]] auto create_renderer(SDL_Window &window, std::string_view name)
    -> Renderer;
[[nodiscard]] auto load_texture_from_image(SDL_Renderer &renderer,
                                           const std::filesystem::path &file)
    -> Texture;
} // namespace SDL
