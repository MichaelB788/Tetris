#include "core/tetromino.hpp"

Tetromino::Tetromino(Type type) : m_type(type)
{
  std::map<Type, std::array<Vector2, 4>> shapes{
      {Type::I, {(0, 1), (1, 1), (2, 1), (3, 1)}},
      {Type::O, {(0, 0), (1, 0), (0, 1), (1, 1)}},
      {Type::T, {(0, 1), (1, 1), (1, 0), (2, 1)}},
      {Type::Z, {(0, 0), (1, 0), (1, 1), (2, 1)}},
      {Type::S, {(0, 1), (1, 1), (1, 0), (2, 0)}},
      {Type::J, {(1, 0), (1, 1), (1, 2), (0, 2)}},
      {Type::L, {(0, 0), (0, 1), (1, 1), (2, 1)}},
  };

  m_coordinates = shapes[type];
}