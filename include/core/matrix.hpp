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
	inline constexpr bool isWithinBounds(const Vector2& coordinate) const {
		return coordinate.x >= 0 && coordinate.y >= 0 && coordinate.x < m_data.size() && coordinate.y < m_data.size();
	};
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

#ifdef DEBUG
	friend test_matrix
#endif
};

#endif
