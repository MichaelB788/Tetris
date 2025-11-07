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

	/// @brief Checks for cleared lines, returns true if at least one is found
	bool hasClearedLines();

	/// @brief Clears all completed lines and drops any floating lines.
	void clearLines();

	void placeActor(const Tetromino& actor);
	void removeActor(const Tetromino& actor);
	void groundActor(const Tetromino& actor);

	bool actorCollidesGround(const Tetromino& actor) const;
	bool actorCollidesWall(const Tetromino& actor) const;
	bool actorIsOutOfBounds(const Tetromino& actor) const;

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
	std::array<bool, HEIGHT> getRowState() const;
	void dropFloatingRows(const std::array<bool, HEIGHT>& rowState);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
	Tetromino m_ghost{TetrominoType::NONE, {5, 5}}; // Temporary value
};

#endif
