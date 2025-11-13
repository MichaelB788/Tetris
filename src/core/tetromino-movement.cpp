#include "core/tetromino-movement.hpp"

bool TetrominoMovement::moveTetromino(Tetromino& actor, Matrix& scene, Direction::Horizontal direction) {
	bool hasMoved = true;
	scene.removeTetromino(actor);
	actor.shift(Vector2::getHorizontal(direction));

	if (scene.doesTetrominoCollideImpermeable(actor)) {
		actor.shift(-Vector2::getHorizontal(direction));
		hasMoved = false;
	}

	scene.placeTetromino(actor);
	return hasMoved;
}

bool TetrominoMovement::moveTetrominoDown(Tetromino& actor, Matrix& scene) {
	scene.removeTetromino(actor);
	actor.shift(Vector2::down());

	if (scene.doesTetrominoCollideGround(actor)) {
		actor.shift(Vector2::up());
		scene.lockDownTetromino(actor);
		return false;
	}
	else {
		scene.placeTetromino(actor);
	}

	return true;
}

void TetrominoMovement::dropTetromino(Tetromino& actor, Matrix& scene) {
	scene.removeTetromino(actor);
	while (!scene.doesTetrominoCollideGround(actor)) {
		actor.shift(Vector2::down());
	}
	actor.shift(Vector2::up());
	scene.lockDownTetromino(actor);
}
