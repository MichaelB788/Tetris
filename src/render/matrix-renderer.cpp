#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrix() const {
	for (unsigned int y = 0; y < Matrix::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < Matrix::WIDTH; x++)
		{
			if (r_matrix(x, y).state == TileState::EMPTY) {
				r_renderer.drawRectangle(
						Renderer::Color::GRAY, false, x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE
						);
			}
			else if (r_matrix(x, y).state == TileState::ACTIVE || r_matrix(x, y).state == TileState::GROUND)
			{
				r_renderer.drawRectangle(
						Renderer::Color::WHITE, true, x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE
						);
				r_renderer.drawRectangle(
						Renderer::Color::BLACK, false, x * TILE_SIZE, y * TILE_SIZE,
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
