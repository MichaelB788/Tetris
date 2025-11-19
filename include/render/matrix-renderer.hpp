#ifndef MATRIX_RENDERER_H
#define MATRIX_RENDERER_H
#include "core/matrix.hpp"
#include "util/geometry.hpp"
#include "util/renderer.hpp"

class MatrixRenderer {
public:
	static constexpr int TILE_SIZE = 40;

	MatrixRenderer(int tileSize = TILE_SIZE)
		: tileSize(tileSize),
			pixelDimensions(Matrix::WIDTH * tileSize, Matrix::HEIGHT * tileSize),
			offset(0, 0)
	{}

	Dimension2D getPixelDimensions() const { return pixelDimensions; }
	Vector2 getOffset() const { return offset * tileSize; }
	int getTileSize() const { return tileSize; }

	void render(const Matrix& matrix, const Renderer& renderer, const Dimension2D windowDimension);

private:
	Vector2 getPixelPosition(Vector2 pos, Vector2 offset) const {
		return (pos + offset) * tileSize;
	}

	Renderer::Color getTileColor(MatrixTile tile) const;

	void renderTileAt(Vector2 pos, Vector2 offset, const MatrixTile& tile, const Renderer& renderer) const;

	void drawTile(const Renderer& renderer, Renderer::Color color, Vector2 pos, bool filled = false) const;

private:
	int tileSize;
	Dimension2D pixelDimensions;
	Vector2 offset;
};

#endif
