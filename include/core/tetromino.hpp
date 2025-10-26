#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <stdint.h>
#include "util/vector2.hpp"

enum class TetrominoType : uint8_t { I, O, T, Z, S, J, L };

/// @brief A piece of a certain type. Contains information regarding it's shape.
class Tetromino {
private:
	using Coordinates = std::array<Vector2, 4>;
  TetrominoType m_type;
	Coordinates m_coordinates;

public:
  Tetromino(TetrominoType type, Vector2 pivot);
	constexpr TetrominoType type() { return m_type; }
	/// @brief Returns the Tetromino's coordinates, which is an array of Vector2 with a size of 4
	constexpr Coordinates& coordinates() { return m_coordinates; }

  constexpr void moveLeft() { for (auto& c : m_coordinates) c.x--; }
  constexpr void moveRight() { for (auto& c : m_coordinates) c.x++; }
  constexpr void moveDown() { for (auto& c : m_coordinates) c.y++; }
  constexpr void moveUp() { for (auto& c : m_coordinates) c.y--; }

  void rotateClockwise();
  void rotateCounterclockwise();
};

#endif
