#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <random>
#include "util/vector2.hpp"
#include "core/tetromino-type.hpp"
#include "core/tetromino-generator.hpp"

class Tetromino {
public:
	/// @brief Generates a Tetromino of a random type centered at `initialPos`
	Tetromino(Vector2 initialPos);

	/// @brief Generates a Tetromino of `Tetromino::Type type` centered at `initialPos`
	Tetromino(TetrominoType type, Vector2 initialPos);

	/// @return The type assosciated with this Tetromino
	TetrominoType getType() const { return type; } 

	/// @return The type assosciated with this Tetromino
	uint8_t getCurrentRotationState() const { return rotationState; } 

	/// @brief Applies the translation vector to each coordinate of Tetromino's blocks
	void shift(Vector2 translation);

	/// @brief Shifts every block of this Tetromino by (dx, dy) 
	void shift(int dx, int dy);

	/// @brief Rotates this Tetromino 90 degrees clockwise or counterclockwise
	void rotate(Direction::Rotation direction);

	// Iterator
	using const_iterator = std::array<Vector2, 4>::const_iterator;

	const_iterator begin() const { return blocks.begin(); }
	const_iterator end() const { return blocks.end(); }

	const_iterator cbegin() const { return blocks.cbegin(); }
	const_iterator cend() const { return blocks.cend(); }

private:
	void updateRotationState(Direction::Rotation direction);

private:
	std::array<Vector2, 4> blocks;
	TetrominoType type;
	uint8_t rotationState = 0;
};

#endif
