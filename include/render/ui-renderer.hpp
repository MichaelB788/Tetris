#ifndef RENDER_UI
#define RENDER_UI
#include "util/renderer.hpp"
#include "util/text.hpp"
#include "util/geometry.hpp"
#include "render/matrix-renderer.hpp"

class UIRenderer {
public:
	UIRenderer(SDL_Renderer* renderer)
		: storedText("Stored", renderer),
			nextText("Next", renderer),
			offset(0, 40)
	{};

	void renderText(const Renderer& renderer, const MatrixRenderer& matrixRenderer);
	void renderStoredAndNext(const Tetromino& stored, const Tetromino& next);

private:
	Text storedText;
	Text nextText;
	Vector2 offset;
};

#endif
