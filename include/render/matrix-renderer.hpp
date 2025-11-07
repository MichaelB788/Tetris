#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include "core/tile-state.hpp"
#include "core/matrix.hpp"
#include "util/renderer.hpp"

class MatrixRenderer {
public:
	MatrixRenderer(Matrix& matrix, Renderer& renderer) :
		r_matrix(matrix),
		r_renderer(renderer)
	{};
	void renderMatrix();

private:
	constexpr static unsigned int TILE_SIZE = 40;
	Matrix& r_matrix;
	Renderer& r_renderer;
};

#endif
