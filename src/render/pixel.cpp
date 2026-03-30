#include "render/pixel.hpp"
#include "util/Point.hpp"
#include <SDL3/SDL_render.h>

void pixel::draw_tetromino_tile(SDL_Renderer &renderer, SDL_Texture &atlas,
                                SDL_FRect atlas_src, Point dest, Point offset) {
  const SDL_FRect tile = {
      .x = static_cast<float>(dest.x * pixel::SIZE + offset.x),
      .y = static_cast<float>(dest.y * pixel::SIZE + offset.y),
      .w = pixel::SIZE,
      .h = pixel::SIZE};
  SDL_RenderTexture(&renderer, &atlas, &atlas_src, &tile);
}
