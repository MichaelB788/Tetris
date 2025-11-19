#ifndef UI_RENDERER_H
#define UI_RENDERER_H
#include "core/game-state.hpp"
#include "render/matrix-renderer.hpp"
#include "render/text-renderer.hpp"
#include "render/tetromino-renderer.hpp"

class UIRenderer {
public:
	explicit UIRenderer(SDL_Renderer* renderer, const GameState& gameState)
		: textRenderer(renderer),
			tetrominoRenderer(gameState.getNext(), gameState.getStored())
	{}

	void render(const Renderer& renderer, const MatrixRenderer& matrixRenderer);

private:
	TextRenderer textRenderer;
	TetrominoRenderer tetrominoRenderer;
};

#endif
