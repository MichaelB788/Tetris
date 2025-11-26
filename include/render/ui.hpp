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
			uiBox(TetrisRenderer::MATRIX_PIXEL_SIZE)
	{}

	void render(const GameState& gameState, Dimension2D windowSize);

private:
	void renderTetrominoQueue(const TetrominoQueue& queue) const;

private:
	const Renderer& renderer;
	Rectangle uiBox;
};

#endif
