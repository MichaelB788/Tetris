#include "platform/PlatformSDL_IMG.hpp"
#include <SDL3_image/SDL_image.h>

auto sdl::img::create_surface_from_img(const std::filesystem::path &path_to_img)
    -> Surface {
  if (!std::filesystem::exists(path_to_img)) {
    throw std::invalid_argument(
        std::string("Could not create SDL surface. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());
  }

  if (auto raw_surface = IMG_Load(path_to_img.c_str()))
    return Surface(raw_surface);

  throw sdl::Exception("Could not load image to SDL surface");
}

auto sdl::img::create_texture_from_img(SDL_Renderer *renderer,
                                       const std::filesystem::path &path_to_img)
    -> Texture {
  if (!std::filesystem::exists(path_to_img)) {
    throw std::invalid_argument(
        std::string("Could not create SDL texture. Provided path to image does "
                    "not exist: ") +
        path_to_img.string());
  }

  if (auto raw_texture = IMG_LoadTexture(renderer, path_to_img.c_str()))
    return Texture(raw_texture);

  throw sdl::Exception("Failed to create SDL texture from file");
}
