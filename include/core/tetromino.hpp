#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "util/vector2.hpp"
#include "core/tetromino-type.hpp"

class Tetromino {
public:
	/// @brief Generates a Tetromino of a random type centered at `initialPos`
	Tetromino(Vector2 initialPos);
	/// @brief Generates a Tetromino of `Tetromino::Type type` centered at `initialPos`
	Tetromino(TetrominoType type, Vector2 initialPos);

	inline TetrominoType type() const { return tetrominoType; } 

	/// @brief Adds `translation` to each point in this Tetromino's coordinates
	void shift(Vector2 translation);
	void shift(int dx, int dy);

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Direction::Rotation rotation);

	// === Iterator ===
	using iterator = std::array<Vector2, 4>::iterator;
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	iterator begin() { return blocks.begin(); }
	iterator end() { return blocks.end(); }

	const_iterator begin() const { return blocks.begin(); }
	const_iterator end() const { return blocks.end(); }

	const_iterator cbegin() const { return blocks.cbegin(); }
	const_iterator cend() const { return blocks.cend(); }

private:
	std::array<Vector2, 4> blocks;
	TetrominoType tetrominoType;
};

#endif
