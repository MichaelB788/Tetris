#include "core/tetromino-operations.hpp"

void TetrominoOperation::rotate(Tetromino& piece) {
  // HACK: This is assuming index 2 is actually the center of the piece.
  Vector2 origin = piece.m_coordinates[2];

  for (auto &coordinate : piece.m_coordinates) {
    // Translate to origin
    int8_t dx = coordinate.x - origin.x;
    int8_t dy = coordinate.y - origin.y;

    // Rotate 90° counterclockwise: (x,y) -> (-y,x)
    int8_t rotated_x = -dy;
    int8_t rotated_y = dx;

    // Translate back
    coordinate.x = origin.x + rotated_x;
    coordinate.y = origin.y + rotated_y;
  }
}

void move(Tetromino& piece, Direction dir) {
  for (auto &tile : piece.m_coordinates) {
    switch (dir) {
    case Direction::RIGHT:
      tile.x++;
      break;
    case Direction::LEFT:
      tile.x--;
      break;
    case Direction::DOWN:
      tile.y++;
      break;
    default:
      break;
    }
  }
}

Tetromino::Type TetrominoOperation::generateRandomType() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 7);
  return Tetromino::Type(distrib(gen));
}