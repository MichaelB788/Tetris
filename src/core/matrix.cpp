#include "core/matrix.hpp"

Matrix::Matrix() {
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

void Matrix::occupy(unsigned int x, unsigned int y, TetrominoType type) {
	m_data[y * WIDTH + x].occupy(type); 
}

void Matrix::set(unsigned int x, unsigned int y, MatrixTile type) {
	m_data[y * WIDTH + x] = type; 
}

void Matrix::clearMatrix() {
  for (int i = 0; i < m_data.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			m_data[i].clear();
  }
}

void Matrix::clearAndDropCompletedRows() {
	clearFilledRows();
	dropRows(flagPopulatedRows());
};

bool Matrix::placeTetromino(Tetromino& actor) {
	for (const auto& c : actor.coordinates()) {
		if (!isWithinBounds(c) || get(c.x, c.y).isImpermiable()) return false;
	}
	for (const auto& c : actor.coordinates()) {
		occupy(c.x, c.y, actor.type());
	}
	return true;
}

bool Matrix::removeTetromino(Tetromino& actor) {
	for (const auto& c : actor.coordinates()) {
		if (!isWithinBounds(c) || get(c.x, c.y).isImpermiable()) return false;
	}
	for (const auto& c : actor.coordinates()) {
		get(c.x, c.y).clear();
	}
	return true;
}

constexpr bool Matrix::isWithinBounds(const Vector2& coordinate) const {
	return coordinate.x >= 0 && coordinate.y >= 0 && coordinate.x < m_data.size() && coordinate.y < m_data.size();
};

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
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		get(col, row).clear();
}

void Matrix::fillRow(unsigned int row, MatrixTile tile) {
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		set(col, row, tile);
}

void Matrix::replaceAndClearRow(unsigned int replacedRow, unsigned int clearedRow) {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		set(col, replacedRow, get(col, clearedRow));
		get(col, clearedRow).clear();
	}
}

void Matrix::clearFilledRows() {
	for (unsigned int row = 0; row < HEIGHT; row++)
		if (isRowComplete(row)) clearRow(row);
}

constexpr std::array<bool, Matrix::HEIGHT> Matrix::flagPopulatedRows() const {
	std::array<bool, HEIGHT> populatedRows;
	for (unsigned int row = HEIGHT - 1; row >= 0; row--) {
		populatedRows.at(row) = ( isRowPopulated(row) ) ? true : false;
	}
	return populatedRows;
}

void Matrix::dropRows(const std::array<bool, HEIGHT>& floatingRows) {
	for (unsigned int i = 0; i < HEIGHT - 1; i++) {
		if (floatingRows.at(i) == 0) {
			unsigned int j = 0;
			while (floatingRows.at(j) == 0 && j < HEIGHT) j++; 
			if (j < HEIGHT) replaceAndClearRow(i, j);
		}
	}
}
