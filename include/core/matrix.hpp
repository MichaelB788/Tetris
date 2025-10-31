#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdint.h>
#include "core/tetromino.hpp"
#include "core/tile-state.hpp"

/// @brief The Tetris playfield. Tiles are stored and represented by their state.
class Matrix {
public:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 24;

	Matrix();

	MatrixTile& get(unsigned int x, unsigned int y);
	const MatrixTile& get(unsigned int x, unsigned int y) const;

	void clearMatrix();
	void clearAndDropCompletedRows();
	bool canPlace(Tetromino& actor);
	bool place(Tetromino& actor);
	bool remove(Tetromino& actor);

protected:
	void occupy(unsigned int x, unsigned int y, TetrominoType type);
	void set(unsigned int x, unsigned int y, MatrixTile type);

	// === Query ===
	constexpr bool isWithinBounds(const Vector2& coordinate) const;
	constexpr bool isComplete(unsigned int row) const;
	constexpr bool isEmpty(unsigned int row) const;
	constexpr bool isPopulated(unsigned int row) const;

	// === Operations ===
	void clear(unsigned int row);
	void fill(unsigned int row, MatrixTile tile);
	void replaceAndClear(unsigned int replacedRow, unsigned int clearedRow);
	void clearFilledRows();

	// === Gravity logic ===
	constexpr std::array<bool, HEIGHT> getRowState() const;
	void dropFloatingRows(const std::array<bool, HEIGHT>& rowState);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
};

#endif
