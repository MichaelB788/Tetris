#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

struct GameState {
	bool currentHasBeenSwapped = false;
	Matrix matrix;
	Tetromino currentTetromino;
	Tetromino nextTetromino;
	Tetromino storedTetromino;

	GameState()
		: currentTetromino({TetrominoType::I, Matrix::TETROMINO_INITIAL_POS}),
			nextTetromino(generateRandomTetromino()),
			storedTetromino(generateNullTetromino())
	{}

	void update();
	void gameOver();

	void switchToNextTetromino();
	void swapActorWithStored();

private:
	void resetTetromino();

	inline const Tetromino generateRandomTetromino() {
		return Tetromino({Matrix::TETROMINO_INITIAL_POS});
	};
	inline const Tetromino generateNullTetromino() {
		return Tetromino(TetrominoType::NONE, {Matrix::TETROMINO_INITIAL_POS});
	};
};

#endif
