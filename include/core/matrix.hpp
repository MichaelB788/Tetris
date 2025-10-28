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

	constexpr Matrix();

	MatrixTile& get(unsigned int x, unsigned int y);
	const MatrixTile& get(unsigned int x, unsigned int y) const;
	void set(unsigned int x, unsigned int y, TetrominoType type);
	void set(unsigned int x, unsigned int y, MatrixTile type);

	void clearMatrix();
	void clearAndDropCompletedRows();
	bool placeTetromino(Tetromino& actor);

protected:
	constexpr bool isWithinBounds(const Vector2& coordinate) const;
	constexpr bool isRowComplete(unsigned int row) const;
	constexpr bool isRowEmpty(unsigned int row) const;
	constexpr bool isRowPopulated(unsigned int row) const;

	void clearRow(unsigned int row);
	void fillRow(unsigned int row, TetrominoType type);
	void replaceAndClearRow(unsigned int replacedRow, unsigned int clearedRow);
	void clearRows();

	constexpr std::array<bool, HEIGHT> getPopulatedRows() const;
	void dropRows(const std::array<bool, HEIGHT>& populatedRows);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
};

#endif
