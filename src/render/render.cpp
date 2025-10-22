#include "render/render.hpp"

void Render::rectangle(SDL_Renderer *renderer, unsigned int x, unsigned int y, unsigned int h, unsigned int w) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Render::tetrisMatrix(SDL_Renderer* renderer, Matrix& matrix) {
	constexpr unsigned int TILE_SIZE = Screen::WIDTH / 15;

	for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++) {
		for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++) {
			Render::rectangle(renderer, x, y, TILE_SIZE, TILE_SIZE);
		}
	}
}
