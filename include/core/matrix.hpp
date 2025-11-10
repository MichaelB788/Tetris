#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdint.h>
#include <cassert>
#include "core/tetromino.hpp"
#include "core/matrix-tile.hpp"

/// @brief The Tetris playfield manages its own state as well as any given Tetromino.
class Matrix {
public:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 24;

	Matrix();

	inline const MatrixTile& operator()(unsigned int x, unsigned int y) const {
		return m_data[mapIndex(x, y)];
	};
	inline const MatrixTile& operator()(Vector2 vec) const {
		return m_data[mapIndex(vec)];
	};
	inline MatrixTile& operator()(unsigned int x, unsigned int y) {
		return m_data[mapIndex(x, y)];
	};
	inline MatrixTile& operator()(Vector2 vec) {
		return m_data[mapIndex(vec)];
	};

	void assignActor(const Tetromino* actor);

	bool tetrominoIsOutOfBounds(const Tetromino& tetromino) const;
	void dropTetromino(Tetromino& tetromino) const;

	void clearMatrix();
	void checkAndClearLines();

	void placeActor();
	void removeActor();
	void groundActor();

	bool actorCollidesGround() const;
	bool actorCollidesImpermiable() const;

private:
	constexpr size_t mapIndex(unsigned int x, unsigned int y) const {
		size_t index = y * WIDTH + x;
		assert(index >= 0 && index < m_data.size() && "Attempting to access element outside range of m_data");
		return index;
	}
	constexpr size_t mapIndex(Vector2 vec) const {
		size_t index = vec.y * WIDTH + vec.x;
		assert(index >= 0 && index < m_data.size() && "Attempting to access element outside range of m_data");
		return index;
	}

	// === Query ===
	bool isRowComplete(unsigned int row) const;
	bool isRowEmpty(unsigned int row) const;
	bool tetrominoCollides(const Tetromino& tetromino, MatrixTile::State state) const;

	// === Ghost Operations ===
	void placeGhost();
	void removeGhost();

	// === Row Operations ===
	void clearRow(unsigned int row);
	void replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow);
	bool clearFilledRows();
	void dropFloatingRows();

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;

	/// @note This is a non-owning reference.
	const Tetromino* p_actor;
	Tetromino m_ghost {TetrominoType::NONE, {5, 5}};
};

#endif
