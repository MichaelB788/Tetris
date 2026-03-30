#pragma once
#include <SDL3/SDL_rect.h>
#include <array>

class SDL_Renderer;
class SDL_Texture;
class Point;

namespace pixel {
inline constexpr float SIZE = 32;

inline constexpr float COL_0 = 0, COL_1 = SIZE, COL_2 = SIZE * 2,
                       COL_3 = SIZE * 3;
inline constexpr float ROW_0 = 0, ROW_1 = SIZE;

inline constexpr std::array<SDL_FRect, 8> textures_src{{
    {.x = COL_0, .y = ROW_0, .w = SIZE, .h = SIZE}, // I
    {.x = COL_1, .y = ROW_0, .w = SIZE, .h = SIZE}, // O
    {.x = COL_2, .y = ROW_0, .w = SIZE, .h = SIZE}, // T
    {.x = COL_3, .y = ROW_0, .w = SIZE, .h = SIZE}, // S
    {.x = COL_0, .y = ROW_1, .w = SIZE, .h = SIZE}, // Z
    {.x = COL_1, .y = ROW_1, .w = SIZE, .h = SIZE}, // J
    {.x = COL_2, .y = ROW_1, .w = SIZE, .h = SIZE}, // L
    {.x = COL_3, .y = ROW_1, .w = SIZE, .h = SIZE}, // Garbage
}};

template <typename T> constexpr SDL_FRect texture_src(T type) {
  return textures_src[static_cast<std::size_t>(type)];
}

void draw_tetromino_tile(SDL_Renderer &renderer, SDL_Texture &atlas,
                         SDL_FRect atlas_src, Point dest, Point offset);
} // namespace pixel
