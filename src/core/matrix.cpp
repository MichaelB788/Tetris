#include "core/matrix.hpp"

Matrix::Matrix() {
  for (int i = 0; i < m_data.size(); i++) {
		m_data[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 ) ?
			MatrixTile(TileState::WALL) : MatrixTile(TileState::EMPTY);
  }
}

void Matrix::clearMatrix() {
  for (int i = 0; i < m_data.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			m_data[i].clear();
  }
}

void Matrix::clearLines() {
	clearFilledRows();
	dropFloatingRows(getRowState());
};

bool Matrix::assignActor(Tetromino* actor) {
	if (tetrominoIsWithinBounds(actor)) {
		p_actor = actor;
		return true;
	} else {
		return false;
	}
}

void Matrix::placeActor() {
	if (tetrominoIsWithinBounds(p_actor)) {
		for (const auto& c : p_actor->coordinates()) {
			get(c.x, c.y).occupy(p_actor->type());
		}
	}
}

void Matrix::groundActor() {
	if (tetrominoIsWithinBounds(p_actor)) {
		for (const auto& c : p_actor->coordinates()) {
			get(c.x, c.y).ground();
		}
	}
}

void Matrix::removeActor() {
	if (tetrominoIsWithinBounds(p_actor)) {
		for (const auto& c : p_actor->coordinates()) {
			get(c.x, c.y).clear();
		}
	}
}

bool Matrix::actorCollidesGround() {
	if (tetrominoIsWithinBounds(p_actor)) {
		for (const auto& c : p_actor->coordinates()) {
			if (get(c.x, c.y).isGround()) return true;
		}
	}
	return false;
}

MatrixTile& Matrix::get(unsigned int x, unsigned int y) {
	return m_data[y * WIDTH + x];
}

const MatrixTile& Matrix::get(unsigned int x, unsigned int y) const {
	return m_data[y * WIDTH + x];
}

void Matrix::set(unsigned int x, unsigned int y, MatrixTile type) {
	m_data[y * WIDTH + x] = type; 
}

bool Matrix::tetrominoIsWithinBounds(const Tetromino* tetromino) const {
	if (tetromino != nullptr)
	{
		for (const auto& c : tetromino->coordinates()) {
			if (c.x < 0 || c.y < 0 || c.x >= WIDTH || c.y >= HEIGHT) return false;
		}
		return true;
	} else {
		return false;
	}
};

constexpr bool Matrix::isRowComplete(unsigned int row) const {
	for (unsigned int x = 1; x < WIDTH - 1; x++) {
		if (get(x, row).isEmpty()) return false;
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

void Matrix::replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow) {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		set(col, replacedRow, get(col, clearedRow));
		get(col, clearedRow).clear();
	}
}

void Matrix::clearFilledRows() {
	for (unsigned int row = 0; row < HEIGHT; row++)
		if (isRowComplete(row)) clearRow(row);
}

constexpr std::array<bool, Matrix::HEIGHT> Matrix::getRowState() const {
	std::array<bool, HEIGHT> populatedRows;
	for (unsigned int row = HEIGHT - 1; row >= 0; row--) {
		populatedRows.at(row) = ( isRowPopulated(row) ) ? true : false;
	}
	return populatedRows;
}

void Matrix::dropFloatingRows(const std::array<bool, HEIGHT>& rowState) {
	for (unsigned int i = 0; i < HEIGHT - 1; i++) {
		if (rowState.at(i) == 0) {
			unsigned int j = 0;
			while (rowState.at(j) == 0 && j < HEIGHT) j++; 
			if (j < HEIGHT) replaceAndClearRows(i, j);
		}
	}
}
