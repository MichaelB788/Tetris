#include "core/command.hpp"
#include "core/matrix-operations.hpp"

void Command::move(Tetromino& actor, Direction dir, Matrix& scene) {
	std::array<Vector2, 4> previousCoordinates = actor.m_coordinates;
	TetrominoOperation::move(actor, dir);

	if (MatrixOperation::canPlaceTetromino(actor.m_coordinates, scene)) {
		MatrixOperation::removeTetromino(previousCoordinates, scene);
		MatrixOperation::placeTetromino(actor.m_coordinates, scene);
	} else {
		actor.m_coordinates = previousCoordinates;
	}
}

void Command::rotate(Tetromino& actor, Matrix& scene) {
	std::array<Vector2, 4> previousCoordinates = actor.m_coordinates;
	TetrominoOperation::rotate(actor);

	// TODO: Implement RSS and come back to this
	if (MatrixOperation::canPlaceTetromino(actor.m_coordinates, scene)) {
		MatrixOperation::removeTetromino(previousCoordinates, scene);
		MatrixOperation::placeTetromino(actor.m_coordinates, scene);
	} else {
		actor.m_coordinates = previousCoordinates;
	}
}

void Command::drop(Tetromino& actor, Matrix& scene) {
	while (MatrixOperation::canPlaceTetromino(actor.m_coordinates, scene)) {
		TetrominoOperation::move(actor, Direction::DOWN);
	}
	TetrominoOperation::move(actor, Direction::UP);
	MatrixOperation::placeTetromino(actor.m_coordinates, scene);
}
