#pragma once
#include "platform/PlatformSDL.hpp"
#include <filesystem>

namespace sdl::img {
[[nodiscard]] auto
create_surface_from_img(const std::filesystem::path &path_to_img) -> Surface;

[[nodiscard]] auto
create_texture_from_img(SDL_Renderer *renderer,
                        const std::filesystem::path &path_to_img) -> Texture;
} // namespace sdl::img
