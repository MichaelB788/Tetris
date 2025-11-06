#include "render/matrix-renderer.hpp"

void MatrixRenderer::renderMatrix() {
	for (unsigned int y = 0; y < Matrix::HEIGHT; y++) {
		for (unsigned int x = 0; x < Matrix::WIDTH; x++) {
			r_matrix.get(x, y);
		}
	}
}

void MatrixRenderer::setTexture(TetrominoType& type) {
	switch(type) {
		case TetrominoType::I:
		case TetrominoType::O:
		case TetrominoType::T:
		case TetrominoType::Z:
		case TetrominoType::S:
		case TetrominoType::J:
		case TetrominoType::L:
		default:
	}
}
