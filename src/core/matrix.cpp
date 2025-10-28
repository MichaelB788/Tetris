#include "core/matrix.hpp"
#include "util/game-constants.hpp"
#include <array>

constexpr Matrix::Matrix() {
  for (int i = 0; i < m_data.size(); i++) {
		m_data[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 ) ?
			MatrixTile(TileState::WALL) : MatrixTile(TileState::EMPTY);
  }
}

MatrixTile& Matrix::get(unsigned int x, unsigned int y) {
	return m_data[y * WIDTH + x];
}

const MatrixTile& Matrix::get(unsigned int x, unsigned int y) const {
	return m_data[y * WIDTH + x];
}

void Matrix::set(unsigned int x, unsigned int y, TetrominoType type) {
	m_data[y * WIDTH + x].occupy(type); 
}

void Matrix::clearMatrix() {
  for (int i = 0; i < m_data.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			m_data[i].clear();
  }
}

void clearAndDropCompletedRows();

void Matrix::placeTetromino(Tetromino& actor) {
	bool success = true;
	for (const auto& c : actor.coordinates()) {
		if (!isWithinBounds(c)) success = false;
	}
	if (success) {
		for (const auto& c : actor.coordinates()) {
			set(c.x, c.y, actor.type());
		}
	}
}

constexpr bool Matrix::isRowComplete(unsigned int row) const {
	for (unsigned int x = 1; x < WIDTH - 1; x++) {
		if (get(x, row).isEmpty()) return false;
	}
	return true;
}

constexpr bool Matrix::isRowEmpty(unsigned int row) const {
	for (unsigned int x = 1; x < WIDTH - 1; x++) {
		if (get(x, row).isImpermiable()) return false;
	}
	return true;
}

constexpr bool Matrix::isRowPopulated(unsigned int row) const {
	for (unsigned int x = 1; x < WIDTH - 1; x++) {
		if (get(x, row).isGround()) return true;
	}
	return false;
}

void Matrix::clearRow(unsigned int row) {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		get(col, row).clear();
	}
}

void Matrix::fillRow(MatrixTile tile, unsigned int row, TetrominoType type) {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		set(col, row, type);
	}
}

void Matrix::clearRows() {
	for (unsigned int y = 0; y < HEIGHT; y++) {
		if (isRowComplete(y)) {
			for (unsigned int x = 1; x < WIDTH - 1; x++) {
				get(x, y).clear();
			}
		}
	}
}
