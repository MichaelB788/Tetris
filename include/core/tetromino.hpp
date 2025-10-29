#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <stdint.h>
#include <random>
#include "util/vector2.hpp"
#include "core/tile-state.hpp"

/// @brief Holds data about the Tetromino's position and type, and can manipulate this data through movement and rotation.
class Tetromino {
public:
	Tetromino(TetrominoType type);
	
	constexpr TetrominoType type() { return m_type; }
	constexpr std::array<Vector2, 4>& coordinates() { return m_coordinates; }

	/// @breif Translates the Tetromino while preserving its shape
	void move(int dx, int dy);
	inline void rotateClockwise() { rotate(true); };
	inline void rotateCounterclockwise() { rotate(false); };

protected:
	void rotate(bool clockwise);

private:
  static TetrominoType typeGenerator();

	TetrominoType m_type;
	std::array<Vector2, 4> m_coordinates;
};

#endif
