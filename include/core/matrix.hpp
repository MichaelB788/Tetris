#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdint.h>
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

	/// @brief Reverts the Matrix to its original, empty state.
	void clearMatrix();

	/// @brief Checks for filled lines, returns true if at least one is found
	bool hasFilledLines();

	/// @brief Clears all completed lines and drops any floating lines.
	void clearLines();

	void placeActor(const Tetromino& actor);
	void removeActor(const Tetromino& actor);
	void groundActor(const Tetromino& actor);

	bool actorCollidesGround(const Tetromino& actor) const;
	bool actorCollidesImpermiable(const Tetromino& actor) const;
	bool actorIsOutOfBounds(const Tetromino& actor) const;

	Vector2 distanceOutOfBounds(const Tetromino& actor);

private:
	constexpr size_t mapIndex(unsigned int x, unsigned int y) const {
		return y * WIDTH + x;
	};
	constexpr size_t mapIndex(Vector2 vec) const {
		return vec.y * WIDTH + vec.x;
	};

	// === Query ===
	Vector2 howFarOutIsVec2(Vector2 vec);
	constexpr bool isRowComplete(unsigned int row) const;
	constexpr bool isRowPopulated(unsigned int row) const;

	// === Ghost Operations ===
	void placeGhost();
	void removeGhost();

	// === Row Operations ===
	void clearRow(unsigned int row);
	void replaceAndClearRows(unsigned int replacedRow, unsigned int clearedRow);
	void clearFilledRows();

	// === Gravity logic ===
	std::array<bool, HEIGHT> getRowState() const;
	void dropFloatingRows(const std::array<bool, HEIGHT>& rowState);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
	Tetromino m_ghost{Tetromino::Type::NONE, {5, 5}}; // Temporary value
};

#endif
