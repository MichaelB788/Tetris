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

	void clearMatrix();
	void clearAndDropCompletedRows();
  void placeTetromino(Tetromino& actor);

private:
  std::array<MatrixTile, WIDTH * HEIGHT> m_data;

	inline constexpr bool isWithinBounds(const Vector2& coordinate) const {
		return coordinate.x >= 0 && coordinate.y >= 0 && coordinate.x < m_data.size() && coordinate.y < m_data.size();
	};
	constexpr bool isRowComplete(unsigned int row) const;
	constexpr bool isRowEmpty(unsigned int row) const;
	constexpr bool isRowPopulated(unsigned int row) const;

	void clearRow(unsigned int row);
	void fillRow(MatrixTile tile, unsigned int row, TetrominoType type);
	void clearRows();
};

#endif
