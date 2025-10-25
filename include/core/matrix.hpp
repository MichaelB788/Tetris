#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include <stdint.h>
#include "util/vector2.hpp"

namespace matrix_dimensions {
  constexpr unsigned int WIDTH = 12;
	constexpr unsigned int HEIGHT = 24;
}

enum class TileState : int8_t {
  EMPTY,
  ACTIVE,
  GHOST,
  GROUND,
  WALL
};

/// @brief The Tetris playfield. Tiles are stored and represented by their state.
class Matrix
{
private:
  std::array<TileState, matrix_dimensions::WIDTH * matrix_dimensions::HEIGHT> m_data;

  inline constexpr unsigned int computeFlatIndex(Vector2 vec) const {
    return vec.y * matrix_dimensions::WIDTH + vec.x;
  }
  inline constexpr unsigned int computeFlatIndex(unsigned int x, unsigned int y) const {
    return y * matrix_dimensions::WIDTH + x;
  }
public:
  Matrix();

  inline TileState &operator()(unsigned int x, unsigned int y) {
		return m_data[computeFlatIndex(x, y)];
  }
  inline TileState &operator()(Vector2 vec) {
    return m_data[computeFlatIndex(vec)];
  }
  inline const TileState &operator()(unsigned int x, unsigned int y) const {
    return m_data[computeFlatIndex(x, y)];
  }
  inline const TileState &operator()(Vector2 vec) const {
    return m_data[computeFlatIndex(vec)];
  }
};

#endif
