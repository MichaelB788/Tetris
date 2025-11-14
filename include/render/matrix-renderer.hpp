#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "core/matrix.hpp"
#include "util/renderer.hpp"
#include "util/window.hpp"

struct MatrixRenderer {
public:
	static void renderMatrixUsingSDL(const Matrix& matrix, const Renderer& renderer, const Window& window);

private:
	static int pos(int index, int offset) {
		return (index + offset) * MatrixRenderer::TILE_SIZE;
	}
	static constexpr unsigned int TILE_SIZE = 40;
	static constexpr int matrixPixelHeight = Matrix::HEIGHT * TILE_SIZE;
	static constexpr int matrixPixelWidth = Matrix::WIDTH * TILE_SIZE;
};

#endif
