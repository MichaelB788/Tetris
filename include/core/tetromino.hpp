#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <stdint.h>
#include "util/vector2.hpp"
#include "core/tile-state.hpp"

/// @brief Holds data about the Tetromino's position and type, and can manipulate this data through movement and rotation.
class Tetromino {
private:
	TetrominoType m_type;
	std::array<Vector2, 4> m_coordinates;

public:
	Tetromino(TetrominoType type, Vector2 pivot);
	constexpr TetrominoType type() { return m_type; }
	constexpr std::array<Vector2, 4>& coordinates() { return m_coordinates; }

	/// @breif Translates the Tetromino while preserving its shape
	inline void move(int dx, int dy) {
		for (auto& vec : m_coordinates) {
			vec.x += dx;
			vec.y += dx;
		}
	};

	void rotate(bool clockwise);
	inline void rotateClockwise() { rotate(true); };
	inline void rotateCounterclockwise() { rotate(false); };
};

#endif
