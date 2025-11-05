#ifndef RENDER_GAME_OBJECTS_H
#define RENDER_GAME_OBJECTS_H
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include "core/tile-state.hpp"
#include "core/matrix.hpp"

class MatrixRenderer {
public:
	MatrixRenderer(Matrix& matrix, SDL_Renderer* renderer)
		: r_matrix(matrix),
			p_renderer(renderer)
	{};
	void renderMatrix();

private:
	void setTexture(TetrominoType& type);

private:
	constexpr static unsigned int TILE_SIZE = 40;
	Matrix& r_matrix;
	SDL_Renderer* p_renderer = nullptr;
};

#endif
