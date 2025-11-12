#include "core/matrix.hpp"

Matrix::Matrix() {
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = ( i % WIDTH == 0 || i % WIDTH == WIDTH - 1 )
			? MatrixTile(MatrixTile::State::WALL)
			: MatrixTile(MatrixTile::State::EMPTY);
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
		if (doesRowOnlyContain(row, MatrixTile::State::GROUND)) {
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

void Matrix::placeActor(const Tetromino& actor) {
	for (const auto& block : actor) {
		matrix[mapIndex(block)].setActive(actor.type());
	}
}

void Matrix::lockDownActor(const Tetromino& actor) {
	for (const auto& block : actor) {
		matrix[mapIndex(block)].setGround(actor.type());
	}
}

void Matrix::removeActor(const Tetromino& actor) {
	for (const auto& block : actor) {
		matrix[mapIndex(block)].clear();
	}
}

Tetromino Matrix::calculateDropPosition(const Tetromino& actor) const {
	Tetromino actorSimulation = actor;
	bool tetrominoHasShifted = false;

	while (!doesActorCollideGround(actorSimulation)) {
		actorSimulation.shift(Vector2::down());
		tetrominoHasShifted = true;
	}

	if (tetrominoHasShifted) actorSimulation.shift(Vector2::up());

	return actorSimulation;
}

bool Matrix::doesActorCollideGround(const Tetromino& actor) const {
	if (isActorOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (matrix[mapIndex(block)].isGround()) return true;
	}
	return false;
}

bool Matrix::doesActorCollideImpermeable(const Tetromino& actor) const {
	if (isActorOutOfBounds(actor)) return true;

	for (const auto& block : actor) {
		if (matrix[mapIndex(block)].isImpermiable()) return true;
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
	if (row >= HEIGHT) return false;

	for (unsigned int col = 1; col < WIDTH - 1; col++) {
		if (matrix[mapIndex(col, row)].state == state) return true;
	}
	return false;
}

bool Matrix::doesRowOnlyContain(unsigned int row, MatrixTile::State state) const {
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
		if (doesRowContain(readRow, MatrixTile::State::GROUND)) {
			copyRow(writeRow, readRow);
			clearRow(readRow);
			writeRow--;
		}
		readRow--;
	}
}
