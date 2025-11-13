#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include "core/matrix.hpp"
#include "util/renderer.hpp"

class MatrixRenderer {
public:
	MatrixRenderer(const Matrix& matrix) : matrix(matrix) {} 
	void renderMatrixUsingSDL(const Renderer& renderer);
private:
	const Matrix& matrix;
	static constexpr unsigned int TILE_SIZE = 40;
};

#endif
