#include "render/render-game-objects.hpp"

void render_game_object::rectangle(SDL_Renderer *renderer, unsigned int x, unsigned int y, unsigned int h, unsigned int w) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void render_game_object::tetrisMatrix(SDL_Renderer* renderer, Matrix& matrix) {
	constexpr unsigned int TILE_SIZE = Screen::WIDTH / 15;

	for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++) {
		for (unsigned int x = 0; x < matrix_dimensions::WIDTH; x++) {
			render_game_object::rectangle(renderer, x, y, TILE_SIZE, TILE_SIZE);
		}
	}
}
