#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include "core/matrix.hpp"
#include "util/renderer.hpp"

struct MatrixRenderer {
	static constexpr unsigned int TILE_SIZE = 40;
	void renderMatrixUsingSDL(const Matrix& matrix, const Renderer& renderer) const;
};

#endif
