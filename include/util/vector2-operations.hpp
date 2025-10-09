#ifndef VECTOR2_OPERATIONS_H
#define VECTOR2_OPERATIONS_H
#include <array>
#include <stdint.h>
#include "util/vector2.hpp"

namespace Vector2Operation {
  std::array<Vector2, 8> adjacentCellsArray(Vector2& pivot);
}

#endif