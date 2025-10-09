#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"

/// @note While the playfield is 10x24, the matrix will be 12x25 to account for the surrounding boundaries
namespace MatrixDimensions {
  constexpr unsigned int WIDTH = 12, HEIGHT = 25;
}

enum class TileState : uint8_t {
  EMPTY = 0,
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
  inline constexpr unsigned int computeFlatIndex(Vector2 coordinate) const {
    if (coordinate.x < 0 || coordinate.y < 0 || coordinate.x >= WIDTH || coordinate.y >= HEIGHT) {
      return 0;
    }
    else return coordinate.y * MatrixDimensions::WIDTH + coordinate.x;
  }
  inline constexpr unsigned int computeFlatIndex(unsigned int x, unsigned int y) const { return y * MatrixDimensions::WIDTH + x; }

public:

  Matrix();

  inline TileState &operator()(unsigned int x, unsigned int y) {
    return m_data[computeFlatIndex(x, y)];
  }
  inline const TileState &operator()(unsigned int x, unsigned int y) const {
    return m_data[computeFlatIndex(x, y)];
  }
  inline TileState &operator()(Vector2 coordinate) {
    return m_data[computeFlatIndex(coordinate)];
  }
  inline const TileState &operator()(Vector2 coordinate) const {
    return m_data[computeFlatIndex(coordinate)];
  }
};

#endif