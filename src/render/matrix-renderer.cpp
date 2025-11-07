#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrix() {
	for (unsigned int y = 0; y < Matrix::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < Matrix::WIDTH; x++)
		{
			MatrixTile current = r_matrix.get(x, y);
			if (current.state == TileState::EMPTY) {
				r_renderer.drawRectangle(
						Renderer::Color::GRAY, false, x * TILE_SIZE, y * TILE_SIZE,
						TILE_SIZE, TILE_SIZE
				);
			}
			else if (current.state == TileState::ACTIVE || current.state == TileState::GROUND)
			{
				r_renderer.drawRectangle(
						Renderer::Color::WHITE, true, x * TILE_SIZE, y * TILE_SIZE,
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
