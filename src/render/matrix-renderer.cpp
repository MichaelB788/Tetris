#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrixUsingSDL(const Matrix& matrix, const Renderer& renderer, const Window& window) {
	int winWidth, winHeight;
	window.getWindowDimensions(winWidth, winHeight);

	int offsetX = (winWidth - matrixPixelWidth) / (2 * TILE_SIZE);
	int offsetY = (winHeight - matrixPixelHeight) / (2 * TILE_SIZE);
	
	bool filled = true;
	for (unsigned int y = 2; y < Matrix::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < Matrix::WIDTH; x++)
		{
			if (matrix(x, y).state == MatrixTile::State::EMPTY) {
				renderer.drawRectangle(
					Renderer::Color::GRAY, !filled,
					pos(x, offsetX), pos(y, offsetY),
					TILE_SIZE, TILE_SIZE
				);
			}
			else if (matrix(x, y).state == MatrixTile::State::ACTIVE || matrix(x, y).state == MatrixTile::State::GROUND)
			{
				renderer.drawRectangle(
					Renderer::Color::WHITE, filled,
					pos(x, offsetX), pos(y, offsetY),
					TILE_SIZE, TILE_SIZE
				);
				renderer.drawRectangle(
					Renderer::Color::BLACK, !filled,
					pos(x, offsetX), pos(y, offsetY),
					TILE_SIZE, TILE_SIZE
				);
			}
			else
			{
				renderer.drawRectangle(
					Renderer::Color::WHITE, !filled,
					pos(x, offsetX), pos(y, offsetY),
					TILE_SIZE, TILE_SIZE
				);
			}
		}
	}
}
