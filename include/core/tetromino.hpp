#ifndef TETROMINO_H
#define TETROMINO_H
#include <stdint.h>
#include <random>
#include "util/vector2.hpp"
#include "core/tile-state.hpp"
#include "core/shape.hpp"

/// @brief Holds data about the Tetromino's position and type, and can manipulate this data through movement and rotation.
class Tetromino : public Shape {
public:
	/// @brief Generates a Tetromino of a random type centered at (0, 0)
	inline Tetromino() : Shape(getRandomType(), {0, 0}) {};

	/// @brief Generates a Tetromino of a certain type centered at (0, 0)
	inline Tetromino(TetrominoType type) : Shape(type, {0, 0}) {};

	/// @brief Generates a Tetromino of a random type centered at the given position
	inline Tetromino(Vector2 initialPos) : Shape(getRandomType(), initialPos) {};

	/// @brief Generates a Tetromino of a certain type at the given position
	inline Tetromino(TetrominoType type, Vector2 initialPos) : Shape(type, initialPos) {};

	void rotateClockwise() override;
	void rotateCounterclockwise() override;

private:
  static TetrominoType getRandomType();
};

#endif
