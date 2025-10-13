#include "core/tetromino-operations.hpp"

void TetrominoOperation::rotate(Tetromino& piece) {
	if (piece.m_type != Tetromino::Type::O) {
		// NOTE: The pivot should ALWAYS be the first Vector2. See the Tetromino constructor.
		constexpr unsigned int PIVOT_INDEX = 0;
		Vector2 pivot = piece.m_coordinates[PIVOT_INDEX];

		for (auto &coordinate : piece.m_coordinates) {
			/**
			 * Translate to pivot
			 * Rotate 90° counterclockwise: (x,y) -> (-y,x)
			 * Translate back
			 **/
			int dx = coordinate.x - pivot.x;
			int dy = coordinate.y - pivot.y;
			int rotated_x = -dy;
			int rotated_y = dx;
			coordinate.x = pivot.x + rotated_x;
			coordinate.y = pivot.y + rotated_y;
		}
	}
}

void TetrominoOperation::move(Tetromino& piece, Direction dir) {
  for (auto &tile : piece.m_coordinates) {
    switch (dir) {
    case Direction::RIGHT:
      tile.x++;
      break;
    case Direction::LEFT:
      tile.x--;
      break;
    case Direction::UP:
      tile.y--;
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
  std::uniform_int_distribution<> distrib(0, 6);
  return Tetromino::Type(distrib(gen));
}
