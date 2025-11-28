#ifndef UI_H
#define UI_H
#include "core/matrix.hpp"
#include "core/tetromino-queue.hpp"
#include "util/geometry.hpp"
#include "render/tetris-renderer.hpp"

class UI {
public:
	UI(const Renderer& renderer)
		: renderer(renderer),
			uiBox(TetrisRenderer::MATRIX_PIXEL_SIZE)
	{}

	void render(const Matrix& matrix, const TetrominoQueue& queue, Dimension2D windowSize);

private:
	void renderTetrominoQueue(const TetrominoQueue& queue) const;

	void renderHeldTetromino(const Tetromino& held) const {
		TetrisRenderer::renderTetromino(held, renderer, {uiBox.pos.x - 200, uiBox.pos.y + 200});
	};

private:
	const Renderer& renderer;
	Rectangle uiBox;
};

#endif
