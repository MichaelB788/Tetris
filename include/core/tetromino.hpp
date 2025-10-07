#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <map>
#include "util/vector2.hpp"
#include "util/game-constants.hpp"

/// @brief A piece of a certain type. Contains information regarding it's shape.
struct Tetromino {
  enum class Type : uint8_t { I, O, T, Z, S, J, L };
  Type m_type;
  std::array<Vector2, 4> m_coordinates;

  /// @param type A Tetromino::Type; I, O, T, Z, S, J, L
  Tetromino(Type type);
};

#endif
