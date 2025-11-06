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

void Matrix::placeActor(const Tetromino& actor) {
	if (actorIsWithinBounds(actor)) {
		for (const auto& c : actor.coordinates()) {
			get(c.x, c.y).occupy(actor.type());
		}
		m_ghost = actor;
		placeGhost();
	}
}

void Matrix::groundActor(const Tetromino& actor) {
	if (actorIsWithinBounds(actor)) {
		for (const auto& c : actor.coordinates()) {
			get(c.x, c.y).ground();
		}
		removeGhost();
	}
}

void Matrix::removeActor(const Tetromino& actor) {
	if (actorIsWithinBounds(actor)) {
		for (const auto& c : actor.coordinates()) {
			get(c.x, c.y).clear();
		}
		removeGhost();
	}
}

bool Matrix::actorCollidesGround(const Tetromino& actor) {
	if (actorIsWithinBounds(actor)) return true;
	for (const auto& c : actor.coordinates()) {
		if (get(c.x, c.y).isGround()) return true;
	}
	return false;
}

bool Matrix::actorCollidesWall(const Tetromino& actor) {
	if (actorIsWithinBounds(actor)) return true;
	for (const auto& c : actor.coordinates()) {
		if (get(c.x, c.y).isWall()) return true;
	}
	return false;
}

bool Matrix::actorIsWithinBounds(const Tetromino& actor) const {
	for (const auto& c : actor.coordinates()) {
		if (c.x < 0 || c.y < 0 || c.x >= WIDTH || c.y >= HEIGHT) return false;
	}
	return true;
}

bool Matrix::hasClearedLines() {
	for (unsigned int row = 0; row < HEIGHT; row++) {
		if (isRowComplete(row)) return true;
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

void Matrix::placeGhost() {
	while (!actorCollidesGround(m_ghost) && actorIsWithinBounds(m_ghost)) {
		m_ghost.shift(Vector2::down());
	}
	m_ghost.shift(Vector2::up());
	for (const auto& c : m_ghost.coordinates()) {
		get(c.x, c.y).occupyAsGhost(m_ghost.type());
	}
}

void Matrix::removeGhost() {
	for (const auto& c : m_ghost.coordinates()) {
		get(c.x, c.y).clear();
	}
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
