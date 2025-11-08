#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "util/renderer.hpp"
#include "render/matrix-renderer.hpp"

class GameState {
public:
	GameState(Renderer& renderer)
		: m_matrixRenderer(m_matrix, renderer),
			m_currentTetromino(generateRandomTetromino()),
			m_nextTetromino(generateRandomTetromino()),
			m_storedTetromino(TetrominoType::NONE, {INIT_X, INIT_Y})
	{};

	void update();
	void gameOver();

	void switchToNextTetromino();
	void swapActorWithStored();

	void moveActor(Vector2::Horizontal direction);
	void moveActorDown();
	void dropActor();

	void rotateActor(Vector2::Rotation rotationDirection);

private:
	inline const Tetromino generateRandomTetromino() {
		return Tetromino({INIT_X, INIT_Y});
	};

private:
	static constexpr unsigned int INIT_X = 5, INIT_Y = 5;

	Matrix m_matrix;
	const MatrixRenderer m_matrixRenderer;
	
	bool m_isSwapped = false;
	Tetromino m_currentTetromino;
	Tetromino m_nextTetromino;
	Tetromino m_storedTetromino;
};

#endif
