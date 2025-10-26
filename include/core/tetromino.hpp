#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <stdint.h>
#include "util/vector2.hpp"

enum class TetrominoType : uint8_t { I, O, T, Z, S, J, L };

/// @brief Holds data about the Tetromino's position and type, and can manipulate this data through movement and rotation.
class Tetromino {
private:
  TetrominoType m_type;
	std::array<Vector2, 4> m_coordinates;

public:
	constexpr TetrominoType type() { return m_type; }
	constexpr std::array<Vector2, 4>& coordinates() { return m_coordinates; }

  constexpr void moveLeft() { for (auto& c : m_coordinates) c.x--; }
  constexpr void moveRight() { for (auto& c : m_coordinates) c.x++; }
  constexpr void moveDown() { for (auto& c : m_coordinates) c.y++; }
  constexpr void moveUp() { for (auto& c : m_coordinates) c.y--; }

  void rotateClockwise();
  void rotateCounterclockwise();
};

#endif
