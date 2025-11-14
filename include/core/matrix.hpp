#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdexcept>
#include <optional>
#include "core/tetromino.hpp"
#include "core/matrix-tile.hpp"

/// @brief The Tetris playfield manages its own state as well as any given Tetromino.
class Matrix {
public:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 24;
	static constexpr Vector2 TETROMINO_INITIAL_POS = {5, 5};

	Matrix();

	const MatrixTile& operator()(unsigned int x, unsigned int y) const {
		return matrix[mapIndex(x, y)];
	};

	const MatrixTile& operator()(Vector2 vec) const {
		return matrix[mapIndex(vec)];
	};

	MatrixTile& operator()(unsigned int x, unsigned int y) {
		return matrix[mapIndex(x, y)];
	};

	MatrixTile& operator()(Vector2 vec) {
		return matrix[mapIndex(vec)];
	};

	/// @brief Reverts the Matrix to its original, empty state.
	void clearMatrix();

	/* *
	 * @brief Clears all completed lines and drops any floating lines on the Matrix.
	 * @return The number of lines cleared
	 */
	unsigned int clearAndDropLines();

	/// @brief Marks the actors tiles as active in the Matrix
	void placeTetromino(const Tetromino& actor);

	/// @brief Marks the actors tiles as empty in the Matrix
	void removeTetromino(const Tetromino& actor);

	/// @brief Marks the actors tiles as grounded in the Matrix
	void lockDownTetromino(const Tetromino& actor);

	/// @brief Determines if the actor is overlapping any grounded tiles
	bool doesTetrominoCollideGround(const Tetromino& actor) const;

	/// @brief Determines if the actor is overlapping any wall or grounded tiles
	bool doesTetrominoCollideImpermeable(const Tetromino& actor) const;

	/// @brief Determines if the actor is out of bounds of the Matrix
	bool isTetrominoOutOfBounds(const Tetromino& actor) const;

private:
	const size_t mapIndex(unsigned int x, unsigned int y) const {
		return ( x >= WIDTH || y >= HEIGHT )
			? throw std::out_of_range("Attempting to access element outside of Matrix")
			: y * WIDTH + x;
	}
	const size_t mapIndex(Vector2 vec) const {
		return mapIndex(vec.x, vec.y);
	}

	// Ghost Operations
	void placeGhost();
	void removeGhost();

	// Row Queries
	bool doesRowContain(unsigned int row, MatrixTile::State state) const;
	bool doesRowOnlyContain(unsigned int row, MatrixTile::State state) const;

	// Row Operations
	void clearRow(unsigned int row);
	void copyRow(unsigned int targetRow, unsigned int copiedRow);
	void dropRowsAbove(unsigned int startingRow);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> matrix;
	Tetromino ghostTetromino = {TetrominoType::NONE, TETROMINO_INITIAL_POS};
};

#endif
