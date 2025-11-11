#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdexcept>
#include "core/tetromino.hpp"
#include "core/matrix-tile.hpp"

/// @brief The Tetris playfield manages its own state as well as any given Tetromino.
class Matrix {
public:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 24;
	static constexpr Vector2 TETROMINO_INITIAL_POS = {5, 2};

	Matrix();

	const MatrixTile& operator()(unsigned int x, unsigned int y) const {
		return m_data[mapIndex(x, y)];
	};

	const MatrixTile& operator()(Vector2 vec) const {
		return m_data[mapIndex(vec)];
	};

	MatrixTile& operator()(unsigned int x, unsigned int y) {
		return m_data[mapIndex(x, y)];
	};

	MatrixTile& operator()(Vector2 vec) {
		return m_data[mapIndex(vec)];
	};

	/// @brief Reverts the Matrix to its original, empty state.
	void clearMatrix();

	/* *
	 * @brief Clears all completed lines and drops any floating lines on the Matrix.
	 * @return The number of lines cleared
	 */
	unsigned int clearAndDropLines();

	/// @brief Marks the actors tiles as active in the Matrix
	void placeActor(const Tetromino& actor);

	/// @brief Marks the actors tiles as empty in the Matrix
	void removeActor(const Tetromino& actor);

	/// @brief Marks the actors tiles as grounded in the Matrix
	void lockDownActor(const Tetromino& actor);

	/// @brief Determines if the actor is overlapping any grounded tiles
	bool doesActorCollideGround(const Tetromino& actor) const;

	/// @brief Determines if the actor is overlapping any wall or grounded tiles
	bool doesActorCollideImpermeable(const Tetromino& actor) const;

	/// @brief Determines if the actor is out of bounds of the Matrix
	bool isActorOutOfBounds(const Tetromino& actor) const;

	/* *
	 * @brief Creates a copy of the actor and simulates a drop command, bringing the Tetromino
	 * down to the lowest empty position on the Matrix.
	 * @return The Tetromino copy used in the simulation.
	 * */
	Tetromino calculateDropPosition(const Tetromino& actor) const;

private:
	const size_t mapIndex(unsigned int x, unsigned int y) const {
		return ( x >= WIDTH || y >= HEIGHT )
			? throw std::out_of_range("Attempting to access element outside of Matrix")
			: y * WIDTH + x;
	}
	const size_t mapIndex(Vector2 vec) const {
		return mapIndex(vec.x, vec.y);
	}

	// Row Queries
	bool doesRowContain(unsigned int row, MatrixTile::State state) const;
	bool doesRowOnlyContain(unsigned int row, MatrixTile::State state) const;

	// Row Operations
	void clearRow(unsigned int row);
	void copyRow(unsigned int targetRow, unsigned int copiedRow);
	void dropRowsAbove(unsigned int startingRow);

private:
	std::array<MatrixTile, WIDTH * HEIGHT> m_data;
};

#endif
