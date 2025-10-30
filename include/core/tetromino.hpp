#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <stdint.h>
#include <random>
#include "util/vector2.hpp"
#include "core/tile-state.hpp"
#include "core/shape.hpp"

/// @brief Holds data about the Tetromino's position and type, and can manipulate this data through movement and rotation.
class Tetromino {
public:
	Tetromino() : m_shape(generateRandomType()) {};
	Tetromino(TetrominoType type) : m_shape(type) {};
	
	inline TetrominoType type() { return m_shape.type(); }
	inline std::array<Vector2, 4> coordinates() { return m_shape.coordinates(); }

	/// @breif Translates the Tetromino while preserving its shape
	inline void shift(int dx, int dy) { m_shape.shift(dx, dy); }

	// TODO: Implement SRS by expanding these functions
	void rotateClockwise();
	void rotateCounterclockwise();

private:
	Shape m_shape;
  static TetrominoType generateRandomType();
};

#endif
