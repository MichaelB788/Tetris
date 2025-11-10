#include "core/matrix.hpp"

Matrix::Matrix() {
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

unsigned int Matrix::clearAndDropLines() {
	unsigned int clearedLines = 0;
	unsigned int firstClearedRow = 0;

	for (unsigned int row = 0; row < HEIGHT; row++) {
		if (doesRowOnlyContain(row, MatrixTile::State::GROUND)) {
			clearRow(row);
			clearedLines++;
			firstClearedRow = row; // Since we're searching from top to bottom, this will naturally end up being the lowest row.
		}
	}

	if (clearedLines > 0) {
		dropRowsAbove(firstClearedRow);
	}

	return clearedLines;
};

void Matrix::placeActor(const Tetromino& actor) {
	if (!isActorOutOfBounds(actor)) {
		for (const auto& block : actor) {
			m_data[mapIndex(block)].setActive(actor.type());
		}
	}
}

void Matrix::lockDownActor(const Tetromino& actor) {
	if (!isActorOutOfBounds(actor)) {
		for (const auto& block : actor) {
			m_data[mapIndex(block)].setGround(actor.type());
		}
	}
}

void Matrix::removeActor(const Tetromino& actor) {
	if (!isActorOutOfBounds(actor)) {
		for (const auto& block : actor) {
			m_data[mapIndex(block)].clear();
		}
	}
}

Tetromino Matrix::calculateDropPosition(const Tetromino& actor) const {
	Tetromino droppedTetromino = actor;
	bool tetrominoHasShifted = false;

	while (!doesActorCollideGround(droppedTetromino)) {
		droppedTetromino.shift(Vector2::down());
		tetrominoHasShifted = true;
	}

	if (tetrominoHasShifted)
		droppedTetromino.shift(Vector2::up());

	return droppedTetromino;
}

bool Matrix::doesActorCollideGround(const Tetromino& actor) const {
	if (isActorOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (m_data[mapIndex(block)].isGround()) return true;
	}
	return false;
}

bool Matrix::doesActorCollideImpermeable(const Tetromino& actor) const {
	if (isActorOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (m_data[mapIndex(block)].isImpermiable()) return true;
	}
	return false;
}

bool Matrix::isActorOutOfBounds(const Tetromino& actor) const {
	for (const auto& block : actor) {
		if (block.x < 0 || block.y < 0 || block.x >= WIDTH || block.y >= HEIGHT) return true;
	}
	return false;
}

bool Matrix::doesRowContain(unsigned int row, MatrixTile::State state) const {
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].state == state) return true;
	}
	return false;
}

bool Matrix::doesRowOnlyContain(unsigned int row, MatrixTile::State state) const {
	bool success = true;
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (m_data[mapIndex(col, row)].state != state) success = false;
	}
	return success;
}

void Matrix::clearRow(unsigned int row) {
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		m_data[mapIndex(col, row)].clear();
}

void Matrix::dropRowsAbove(unsigned int startingRow) {
	for (int emptyRow = startingRow; emptyRow > 0; emptyRow--) {
		if (doesRowOnlyContain(startingRow, MatrixTile::State::EMPTY)) {
			for (int nonEmptyRow = emptyRow - 1; nonEmptyRow >= 0; nonEmptyRow--) {
				if (doesRowContain(nonEmptyRow, MatrixTile::State::GROUND)) {
					for (unsigned int col = 1; col < WIDTH - 1; col++) {
						m_data[mapIndex(col, emptyRow)] = m_data[mapIndex(col, nonEmptyRow)];
						m_data[mapIndex(col, nonEmptyRow)].clear();
					}
				}
			}
		}
	}
}
