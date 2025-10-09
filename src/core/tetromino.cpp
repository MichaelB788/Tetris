#include "core/tetromino.hpp"

Tetromino::Tetromino(Type type, Vector2 pivot) : m_type(type) {
  Vector2 v1, v2, v3;

  switch(type) {
    case Type::I:
    v1 = pivot.rightCell().rightCell();
    v2 = pivot.rightCell();
    v3 = pivot.leftCell();
    break;
    case Type::O:
    v1 = pivot.rightCell();
    v2 = pivot.bottomCell();
    v3 = pivot.bottomCell().rightCell();
    break;
    case Type::T:
    v1 = pivot.leftCell();
    v2 = pivot.rightCell();
    v3 = pivot.topCell();
    break;
    case Type::Z:
    v1 = pivot.topCell().leftCell();
    v2 = pivot.topCell();
    v3 = pivot.rightCell();
    break;
    case Type::S:
    v1 = pivot.leftCell();
    v2 = pivot.topCell();
    v3 = pivot.topCell().rightCell();
    break;
    case Type::J:
    v1 = pivot.topCell().leftCell();
    v2 = pivot.leftCell();
    v3 = pivot.rightCell();
    break;
    case Type::L:
    v1 = pivot.leftCell();
    v2 = pivot.rightCell();
    v3 = pivot.topCell().rightCell();
    break;
    default:
    break;
  }

  m_coordinates = { pivot, v1, v2, v3 };
}