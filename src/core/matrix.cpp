#include "core/matrix.hpp"

Matrix::Matrix() : m_ghost(TetrominoType::NONE, {0, 0}) {
	for (int i = 0; i < m_data.size(); i++) {
		m_data[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 )
			? MatrixTile(MatrixTile::State::WALL)
			: MatrixTile(MatrixTile::State::EMPTY);
	}
}

void Matrix::clearMatrix() {
	for (int i = 0; i < m_data.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			m_data[i].clear();
	}
}

void Matrix::checkAndClearLines() {
	if (clearFilledRows()) {
		dropFloatingRows(getRowState());
	}
};

void Matrix::placeActor(const Tetromino& actor) {
	if (!actorIsOutOfBounds(actor)) {
		m_ghost = actor;
		placeGhost();

		for (const auto& block : actor) {
			m_data[mapIndex(block)].occupy(actor.type());
		}
	}
}

void Matrix::groundActor(const Tetromino& actor) {
	if (!actorIsOutOfBounds(actor)) {
		removeGhost();
		for (const auto& block : actor) {
			m_data[mapIndex(block)].ground(actor.type());
		}
	}
}

void Matrix::removeActor(const Tetromino& actor) {
	if (!actorIsOutOfBounds(actor)) {
		removeGhost();
		for (const auto& block : actor) {
			m_data[mapIndex(block)].clear();
		}
	}
}

void Matrix::dropActor(Tetromino& actor) {
	while (!actorCollidesGround(actor)) {
		actor.shift(Vector2::down());
	}
	actor.shift(Vector2::up());
}

bool Matrix::actorCollidesGround(const Tetromino& actor) const {
	if (actorIsOutOfBounds(actor)) return true;
	for (const auto& block : actor) {
		if (m_data[mapIndex(block)].isGround()) return true;
	}
	return false;
}

bool Matrix::actorCollidesImpermiable(const Tetromino& actor) const {
	if (actorIsOutOfBounds(actor)) return true;
	for (const auto& block : actor) {
		if (m_data[mapIndex(block)].isImpermiable()) return true;
	}
	return false;
}

bool Matrix::actorIsOutOfBounds(const Tetromino& actor) const {
	for (const auto& block : actor) {
		if (block.x < 0 || block.y < 0 || block.x >= WIDTH || block.y >= HEIGHT) return true;
	}
	return false;
}

constexpr bool Matrix::isRowComplete(unsigned int row) const {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].isEmpty()) return false;
	}
	return true;
}

constexpr bool Matrix::isRowPopulated(unsigned int row) const {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].isGround()) return true;
	}
	return false;
}

void Matrix::placeGhost() {
	dropActor(m_ghost);
	for (const auto& block : m_ghost) {
		m_data[mapIndex(block)].occupyAsGhost(m_ghost.type());
	}
}

void Matrix::removeGhost() {
	for (const auto& block : m_ghost) {
		m_data[mapIndex(block)].clear();
	}
}

void Matrix::clearRow(unsigned int row) {
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		m_data[mapIndex(col, row)].clear();
}

void Matrix::replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow) {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		m_data[mapIndex(col, replacedRow)] = m_data[mapIndex(col, clearedRow)];
		m_data[mapIndex(col, clearedRow)].clear();
	}
}

bool Matrix::clearFilledRows() {
	bool cleared = false;
	for (unsigned int row = 0; row < HEIGHT - 1; row++)
		if (isRowComplete(row)) {
			cleared = true;
			clearRow(row);
		}
	return cleared;
}

std::array<bool, Matrix::HEIGHT> Matrix::getRowState() const {
	std::array<bool, HEIGHT> populatedRows;
	for (int row = HEIGHT - 1; row >= 0; row--) {
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
