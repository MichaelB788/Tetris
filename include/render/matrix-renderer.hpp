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
	static Renderer::Color getTetrominoColor(MatrixTile tile);

	static constexpr int TILE_SIZE = 40u;
	static constexpr int MATRIX_PIXEL_HEIGHT = Matrix::HEIGHT * TILE_SIZE;
	static constexpr int MATRIX_PIXEL_WIDTH = Matrix::WIDTH * TILE_SIZE;
};

#endif
