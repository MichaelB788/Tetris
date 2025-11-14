#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrixUsingSDL(const Renderer& renderer) {
	for (unsigned int y = 2; y < Matrix::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < Matrix::WIDTH; x++)
		{
			if (matrix(x, y).state == MatrixTile::State::EMPTY) {
				renderer.drawRectangle(
						Renderer::Color::GRAY, false,
						renderPos(x, 0), renderPos(y, -2),
						TILE_SIZE, TILE_SIZE
						);
			}
			else if (matrix(x, y).state == MatrixTile::State::ACTIVE || matrix(x, y).state == MatrixTile::State::GROUND)
			{
				renderer.drawRectangle(
						Renderer::Color::WHITE, true,
						renderPos(x, 0), renderPos(y, -2),
						TILE_SIZE, TILE_SIZE
						);
				renderer.drawRectangle(
						Renderer::Color::BLACK, false,
						renderPos(x, 0), renderPos(y, -2),
						TILE_SIZE, TILE_SIZE
						);
			}
			else
			{
				renderer.drawRectangle(
						Renderer::Color::WHITE, false,
						renderPos(x, 0), renderPos(y, -2),
						TILE_SIZE, TILE_SIZE
						);
			}
		}
	}
}
