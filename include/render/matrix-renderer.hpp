#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include "core/matrix.hpp"
#include "util/renderer.hpp"

class MatrixRenderer {
public:
	MatrixRenderer(const Matrix& matrix, const Renderer& renderer) :
		r_matrix(matrix),
		r_renderer(renderer)
	{};
	void renderMatrix() const;

private:
	static constexpr unsigned int TILE_SIZE = 40;
	const Matrix& r_matrix;
	const Renderer& r_renderer;
};

#endif
