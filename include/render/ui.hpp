#ifndef UI_H
#define UI_H
#include "core/game-state.hpp"
#include "core/tetromino-queue.hpp"
#include "util/geometry.hpp"
#include "util/text.hpp"
#include "render/tetris-renderer.hpp"

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
	void renderText() const;

	void renderTetrominoQueue(const TetrominoQueue& queue) const;

private:
	const Renderer& renderer;
	Text nextText;
	Text storedText;
	Rectangle uiBox;
};

#endif
