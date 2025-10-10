#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"

/// @note While the playfield is 10x24, the matrix will be 12x25 to account for the surrounding boundaries
namespace MatrixDimensions {
  constexpr unsigned int WIDTH = 12, HEIGHT = 25;
}

enum class TileState : int8_t {
	INVALID = -1,
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
  std::array<TileState, MatrixDimensions::WIDTH * MatrixDimensions::HEIGHT> m_data;

	// TODO: Add a method to verify coordinates
  inline constexpr unsigned int computeFlatIndex(Vector2 vec) const {
    return vec.y * MatrixDimensions::WIDTH + vec.x;
  }
  inline constexpr unsigned int computeFlatIndex(unsigned int x, unsigned int y) const {
    return y * MatrixDimensions::WIDTH + x;
  }

public:

  Matrix();

  inline TileState &operator()(unsigned int x, unsigned int y) {
    return m_data[computeFlatIndex(x, y)];
  }
  inline const TileState &operator()(unsigned int x, unsigned int y) const {
    return m_data[computeFlatIndex(x, y)];
  }
  inline TileState &operator()(Vector2 vec) {
    return m_data[computeFlatIndex(vec)];
  }
  inline const TileState &operator()(Vector2 vec) const {
    return m_data[computeFlatIndex(vec)];
  }
};

#endif
