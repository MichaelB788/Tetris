#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <map>
#include <stdint.h>
#include "util/vector2.hpp"
#include "util/vector2-operations.hpp"

/// @brief A piece of a certain type. Contains information regarding it's shape.
struct Tetromino {
  enum class Type : uint8_t { I = 0, O, T, Z, S, J, L };

  Type m_type;
  std::array<Vector2, 4> m_coordinates;

  Tetromino(Type type, Vector2 pivot);
};

#endif
