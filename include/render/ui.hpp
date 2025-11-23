#ifndef UI_H
#define UI_H
#include "core/game-state.hpp"
#include "util/geometry.hpp"
#include "util/text.hpp"
#include "render/tetris-renderer.hpp"
#include "core/tetromino.hpp"

class UI {
public:
	UI(const Renderer& renderer)
		: renderer(renderer),
			nextText("Next", renderer.getRenderer()),
			storedText("Stored", renderer.getRenderer()),
			uiBox(TetrisRenderer::MATRIX_PIXEL_SIZE)
	{}

	void render(const GameState& gameState, Dimension2D windowSize);

private:
	void renderText(Vector2 position) const;

	void renderTetromino(Vector2 position, const Tetromino& next, const Tetromino& stored) const;

	void renderMatrix(Vector2 pos, const Matrix& matrix) const {
		TetrisRenderer::renderMatrixAt(pos, matrix, renderer);
	}

private:
	const Renderer& renderer;
	Text nextText;
	Text storedText;
	Rectangle uiBox;
};

#endif
