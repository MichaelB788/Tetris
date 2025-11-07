#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrix() {
	for (unsigned int y = 0; y < Matrix::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < Matrix::WIDTH; x++)
		{
			if (r_matrix.get(x, y).isEmpty()) {
				r_renderer.drawRectangle(
						Renderer::Color::GRAY, false, x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE
				);
			}
			else
			{
				r_renderer.drawRectangle(
						Renderer::Color::WHITE, false, x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE
				);
			}
		}
	}
}
