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

	/* *
	 * @brief Assigns internal non-owning reference to an external Tetromino.
	 * @return true if the Tetromino could be placed on the board and the assignment was successful
	 */
	bool assignActor(Tetromino* actor);

	/// @brief Places the current actor on the matrix, if present
	void placeActor();

	/// @brief Removes the current actor on the matrix, if present
	void removeActor();

	/// @brief Grounds the current actor on the matrix, if present
	void groundActor();

	/* *
	 * @brief Checks to see if the current actors coordinates collide with any grounded tiles
	 * @return true if the actor exists and its cooridnates collide with one or more grounded tiles
	 */
	bool actorCollidesGround();

private:
	MatrixTile& get(unsigned int x, unsigned int y);
	const MatrixTile& get(unsigned int x, unsigned int y) const;
	void set(unsigned int x, unsigned int y, MatrixTile tile);

	// === Query ===
	bool tetrominoIsWithinBounds(const Tetromino* tetromino) const;
	constexpr bool isRowComplete(unsigned int row) const;
	constexpr bool isRowPopulated(unsigned int row) const;

	// === Operations ===
	void clearRow(unsigned int row);
	void fillRow(unsigned int row, MatrixTile tile);
	void replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow);
	void clearFilledRows();

	// === Gravity logic ===
	constexpr std::array<bool, HEIGHT> getRowState() const;
	void dropFloatingRows(const std::array<bool, HEIGHT>& rowState);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
	Tetromino* p_actor;
};

#endif
