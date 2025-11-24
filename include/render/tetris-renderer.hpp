#ifndef TETRIS_RENDERER_H
#define TETRIS_RENDERER_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "util/geometry.hpp"
#include "core/matrix-tile.hpp"
#include "util/renderer.hpp"
#include "util/color.hpp"

namespace TetrisRenderer {
	constexpr int TILE_SIZE = 40;

	constexpr Dimension2D MATRIX_PIXEL_SIZE = { Matrix::WIDTH * TetrisRenderer::TILE_SIZE, Matrix::HEIGHT * TetrisRenderer::TILE_SIZE };

	void renderMatrixTile(const Tile& tile, const Renderer& renderer, Vector2 pos = {0, 0}, Vector2 offset = {0, 0});

	void renderMatrix(const Matrix& matrix, const Renderer& renderer, Vector2 offset = {0, 0});

	void renderTetromino(const Tetromino& tetromino, const Renderer& renderer, Vector2 offset = {0, 0});
}

#endif
