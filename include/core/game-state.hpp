#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "core/super-rotation-system.hpp"
#include "util/renderer.hpp"
#include "render/matrix-renderer.hpp"

class GameState {
public:
	GameState(const Renderer& renderer)
		: m_currentTetromino(generateRandomTetromino()),
			m_nextTetromino(generateRandomTetromino()),
			m_storedTetromino(generateNullTetromino()),
			m_matrixRenderer(m_matrix, renderer)
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

private:
	Matrix m_matrix;
	MatrixRenderer m_matrixRenderer;
	
	bool m_currentHasBeenSwapped = false;
	Tetromino m_currentTetromino;
	Tetromino m_nextTetromino;
	Tetromino m_storedTetromino;
};

#endif
