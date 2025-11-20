#include "core/matrix.hpp"

Matrix::Matrix() : ghostTetromino(Tetromino::Type::NONE, TETROMINO_INITIAL_POS) {
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 )
			? Tile(Tile::State::WALL)
			: Tile(Tile::State::EMPTY);
	}
}

void Matrix::clearMatrix() {
	for (int i = 0; i < matrix.size(); i++) {
		if ( i % WIDTH > 0 && i % WIDTH < WIDTH - 1 )
			matrix[i].clear();
	}
}

unsigned int Matrix::clearAndDropLines() {
	unsigned int clearedLines = 0;
	unsigned int lowestClearedRow = 0;

	for (unsigned int row = 0; row < HEIGHT; row++) {
		if (doesRowOnlyContain(row, Tile::State::GROUND)) {
			clearRow(row);
			clearedLines++;
			lowestClearedRow = row; // Since we're searching from top to bottom, this will naturally end up being the lowest row.
		}
	}

	if (clearedLines > 0) {
		dropRowsAbove(lowestClearedRow);
	}

	return clearedLines;
};

void Matrix::placeTetromino(const Tetromino& actor) {
	ghostTetromino = actor;
	placeGhost();
	for (const auto& block : actor) {
		matrix[mapIndex(block)].setActive(actor.getType());
	}
}

void Matrix::lockDownTetromino(const Tetromino& actor) {
	removeGhost();
	for (const auto& block : actor) {
		matrix[mapIndex(block)].setGround(actor.getType());
	}
}

void Matrix::removeTetromino(const Tetromino& actor) {
	removeGhost();
	for (const auto& block : actor) {
		matrix[mapIndex(block)].clear();
	}
}

bool Matrix::doesTetrominoCollideGround(const Tetromino& actor) const {
	if (isTetrominoOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (matrix[mapIndex(block)].state == Tile::State::GROUND) return true;
	}
	return false;
}

bool Matrix::doesTetrominoCollideImpermeable(const Tetromino& actor) const {
	if (isTetrominoOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (matrix[mapIndex(block)].isImpermiable()) return true;
	}
	return false;
}

bool Matrix::isTetrominoOutOfBounds(const Tetromino& actor) const {
	for (const auto& block : actor) {
		if (block.x < 0 || block.y < 0 || block.x >= WIDTH || block.y >= HEIGHT) return true;
	}
	return false;
}

void Matrix::placeGhost() {
	while (!doesTetrominoCollideGround(ghostTetromino)) {
		ghostTetromino.shift(Vector2::down());
	}
	ghostTetromino.shift(Vector2::up());
	for (const auto& block : ghostTetromino) {
		matrix[mapIndex(block)].setGhost(ghostTetromino.getType());
	}
}

void Matrix::removeGhost() {
	for (const auto& block : ghostTetromino) {
		matrix[mapIndex(block)].clear();
	}
}

bool Matrix::doesRowContain(unsigned int row, Tile::State state) const {
	if (row >= HEIGHT) return false;

	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (matrix[mapIndex(col, row)].state == state) return true;
	}
	return false;
}

bool Matrix::doesRowOnlyContain(unsigned int row, Tile::State state) const {
	if (row >= HEIGHT) return false;

	bool success = true;
	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (matrix[mapIndex(col, row)].state != state) success = false;
	}
	return success;
}

void Matrix::clearRow(unsigned int row) {
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		matrix[mapIndex(col, row)].clear();
}

void Matrix::copyRow(unsigned int targetRow, unsigned int copiedRow) {
	for (unsigned int col = 1; col < WIDTH - 1; col++)
		matrix[mapIndex(col, targetRow)] = matrix[mapIndex(col, copiedRow)];
}

void Matrix::dropRowsAbove(unsigned int startingRow) {
	int writeRow = startingRow;
	int readRow = writeRow - 1;

	while (writeRow > 0 && readRow >= 0) {
		if (doesRowContain(readRow, Tile::State::GROUND)) {
			copyRow(writeRow, readRow);
			clearRow(readRow);
			writeRow--;
		}
		readRow--;
	}
}
