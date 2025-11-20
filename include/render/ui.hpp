#ifndef UI_H
#define UI_H
#include "core/game-state.hpp"
#include "util/text.hpp"
#include "render/tetris-renderer.hpp"
#include "core/tetromino.hpp"
#include "util/window.hpp"

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
	void renderText(const Vector2 position) const;

	void renderTetromino(const Vector2 position, const Tetromino& next, const Tetromino& stored) const;

private:
	const Renderer& renderer;
	Text nextText;
	Text storedText;
	Vector2 offset;
	Dimension2D uiBox;
};

#endif
