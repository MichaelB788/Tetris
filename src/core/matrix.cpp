#include "core/matrix.hpp"

Matrix::Matrix() {
	for (int i = 0; i < m_data.size(); i++) {
		m_data[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 )
			? MatrixTile(MatrixTile::State::WALL)
			: MatrixTile(MatrixTile::State::EMPTY);
	}
}

void Matrix::assignActor(const Tetromino* actor) {
	if (!tetrominoIsOutOfBounds(*actor)) {
		p_actor = actor;
	}
	assert(p_actor && "Could not assign Tetromino because it was out of bounds");
}

bool Matrix::tetrominoIsOutOfBounds(const Tetromino& actor) const {
	for (const auto& block : actor) {
		if (block.x < 0 || block.y < 0 || block.x >= WIDTH || block.y >= HEIGHT) return true;
	}
	return false;
}

void Matrix::dropTetromino(Tetromino& actor) const {
	bool shifted = false;
	while (!tetrominoCollides(actor, MatrixTile::State::GROUND)) {
		actor.shift(Vector2::down());
		shifted = true;
	}
	if (shifted) actor.shift(Vector2::up());
}

void Matrix::clearMatrix() {
	for (int i = 0; i < m_data.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			m_data[i].clear();
	}
}

void Matrix::checkAndClearLines() {
	if (clearFilledRows()) {
		dropFloatingRows();
		removeGhost();
	}
};

void Matrix::placeActor() {
	m_ghost = *p_actor;
	placeGhost();

	for (const auto& block : *p_actor) {
		m_data[mapIndex(block)].occupy(p_actor->type());
	}
}

void Matrix::groundActor() {
	removeGhost();
	for (const auto& block : *p_actor) {
		m_data[mapIndex(block)].ground(p_actor->type());
	}
}

void Matrix::removeActor() {
	removeGhost();
	for (const auto& block : *p_actor) {
		m_data[mapIndex(block)].clear();
	}
}

bool Matrix::actorCollidesGround() const {
	return tetrominoCollides(*p_actor, MatrixTile::State::GROUND);
}

bool Matrix::actorCollidesImpermiable() const {
	if (tetrominoIsOutOfBounds(*p_actor)) return true;

	for (const auto& block : *p_actor) {
		if (m_data[mapIndex(block)].isImpermiable()) return true;
	}
	return false;
}

bool Matrix::isRowComplete(unsigned int row) const {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].isEmpty()) return false;
	}
	return true;
}

bool Matrix::isRowEmpty(unsigned int row) const {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].isGround()) return false;
	}
	return true;
}

bool Matrix::tetrominoCollides(const Tetromino& tetromino, MatrixTile::State state) const {
	if (tetrominoIsOutOfBounds(tetromino)) return true;
	for (const auto& block : tetromino) {
		if (m_data[mapIndex(block)].state == state) return true;
	}
	return false;
}

void Matrix::placeGhost() {
	dropTetromino(m_ghost);
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
	for (unsigned int row = 0; row < HEIGHT; row++)
		if (isRowComplete(row)) {
			clearRow(row);
			cleared = true;
		}
	return cleared;
}

void Matrix::dropFloatingRows() {
	for (int emptyRow = HEIGHT - 1; emptyRow > 0; emptyRow--) {
		if (isRowEmpty(emptyRow)) {
			for (int populatedRow = emptyRow - 1; populatedRow >= 0; populatedRow--) {
				if (!isRowEmpty(populatedRow)) {
					replaceAndClearRows(emptyRow, populatedRow);
				}
			}
		}
	}
}
