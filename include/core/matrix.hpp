#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdint.h>
#include "core/tetromino.hpp"
#include "core/tile-state.hpp"

/// @brief The Tetris playfield manages its own state as well as any given Tetromino.
class Matrix {
public:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 24;

	Matrix();

	/// @brief Reverts the Matrix to its original, empty state.
	void clearMatrix();

	/// @brief Clears all completed lines and drops any floating lines.
	void clearLines();

	/// @brief Places the current actor on the matrix, if present
	void placeActor(const Tetromino& actor);

	/// @brief Removes the current actor on the matrix, if present
	void removeActor(const Tetromino& actor);

	/// @brief Grounds the current actor on the matrix, if present
	void groundActor(const Tetromino& actor);

	/* *
	 * @brief Checks to see if the current actors coordinates collide with any grounded tiles
	 * @return true if the actor exists and its cooridnates collide with one or more grounded tiles
	 */
	bool actorCollidesGround(const Tetromino& actor);

	/// @brief Checks to see if the given actor can be placed on the Matrix
	bool actorIsWithinBounds(const Tetromino& actor) const;

	friend class MatrixRenderer;

private:
	MatrixTile& get(unsigned int x, unsigned int y);
	const MatrixTile& get(unsigned int x, unsigned int y) const;
	void set(unsigned int x, unsigned int y, MatrixTile tile);

	// === Query ===
	constexpr bool isRowComplete(unsigned int row) const;
	constexpr bool isRowPopulated(unsigned int row) const;

	// === Ghost Operations ===
	void placeGhost();
	void removeGhost();

	// === Row Operations ===
	void clearRow(unsigned int row);
	void fillRow(unsigned int row, MatrixTile tile);
	void replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow);
	void clearFilledRows();

	// === Gravity logic ===
	constexpr std::array<bool, HEIGHT> getRowState() const;
	void dropFloatingRows(const std::array<bool, HEIGHT>& rowState);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
	Tetromino m_ghost{TetrominoType::NONE, {5, 5}}; // Temporary value
};

#endif
