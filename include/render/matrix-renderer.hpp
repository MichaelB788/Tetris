#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "core/matrix.hpp"
#include "util/renderer.hpp"
#include "util/window.hpp"

class MatrixRenderer {
public:
	static constexpr int TILE_SIZE = 40;

	MatrixRenderer(int tileSize = TILE_SIZE) : tileSize(tileSize) {}

	int getPixelWidth() const { return pixelWidth; }
	int getPixelHeight() const { return pixelHeight; }

	void render(const Matrix& matrix, const Renderer& renderer, const Window& window);

private:
	int gridPixel(int index, int offset) const {
		return (index + offset) * tileSize;
	}
	Renderer::Color getTileColor(MatrixTile tile) const;

	void renderTileAt(const MatrixTile& tile, const Renderer& renderer, int x, int y, int offX, int offY) const;

	void drawTile(const Renderer& renderer, Renderer::Color color, int x, int y, bool filled = false) const;

private:
	int tileSize;
	int pixelWidth = tileSize * Matrix::WIDTH;
	int pixelHeight = tileSize * Matrix::HEIGHT;
};

#endif
