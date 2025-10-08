#ifndef VECTOR2_OPERATIONS_H
#define VECTOR2_OPERATIONS_H
#include <array>
#include <map>
#include <stdint.h>
#include "util/vector2.hpp"

enum class CardinalDirection : uint8_t {
  NORTH_WEST,
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  WEST,
  SOUTH_WEST,
};

namespace Vector2Operation {
  std::array<Vector2, 8> adjacentCellsArray(Vector2& pivot);
  const std::map<CardinalDirection, Vector2> adjacentCellsMap(Vector2& pivot);
}

#endif
