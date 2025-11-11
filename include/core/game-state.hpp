#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "core/super-rotation-system.hpp"

struct GameState {
	bool currentHasBeenSwapped = false;
	Matrix matrix;
	Tetromino currentTetromino;
	Tetromino nextTetromino;
	Tetromino storedTetromino;

	GameState()
		: currentTetromino(generateRandomTetromino()),
			nextTetromino(generateRandomTetromino()),
			storedTetromino(generateNullTetromino())
	{}

	void update();
	void gameOver();

	void switchToNextTetromino();
	void swapActorWithStored();

	void moveActor(Vector2::Horizontal direction);
	void moveActorDown();
	void dropActor();

	void rotateActor(Vector2::Rotation rotationDirection);

private:
	void performSRSTests();
	Vector2 wallKickTranslation() const;
	void resetTetromino();
	inline const Tetromino generateRandomTetromino() {
		return Tetromino({Matrix::TETROMINO_INITIAL_POS});
	};
	inline const Tetromino generateNullTetromino() {
		return Tetromino(TetrominoType::NONE, {Matrix::TETROMINO_INITIAL_POS});
	};
};

#endif
