#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"

namespace MatrixDimensions
{
  const unsigned int WIDTH = 12, HEIGHT = 24;
}

/// @brief A 10 x 24 matrix. Data stored within the Matrix are of TileState.
class Matrix
{
private:
  std::array<TileState, MatrixDimensions::WIDTH * MatrixDimensions::HEIGHT> m_data{};
  inline const unsigned int computeFlatIndex(Vector2 coordinate) const { return coordinate.y * MatrixDimensions::HEIGHT + coordinate.x; }
  inline const unsigned int computeFlatIndex(unsigned int x, unsigned int y) const { return y * MatrixDimensions::HEIGHT + x; }

public:
  Matrix() = default;

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