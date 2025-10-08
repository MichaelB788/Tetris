#include "util/vector2-operations.hpp"

std::array<Vector2, 8> Vector2Operation::adjacentCellsArray(Vector2& pivot) {
  /**
   * Reference: Suppose (0, 0) is the pivot.
   * -1 -1, 0 -1, 1 -1
   * -1  0, 0  0, 1  0
   * -1  1, 0  1, 1  1
   */
  const int STARTING_POS_X = pivot.x - 1; 
  const int STARTING_POS_Y = pivot.y - 1; 
  const int ENDING_POS_X = pivot.x + 1; 
  const int ENDING_POS_Y = pivot.y + 1; 
  std::array<Vector2, 8> adjacentCells;
  unsigned int index = 0;

  for (int y = STARTING_POS_Y; y < ENDING_POS_Y; y++) {
    for (int x = STARTING_POS_X; x < ENDING_POS_X; x++) {
      if ( !(y == pivot.y && x == pivot.x) ) {
        adjacentCells[index++] = Vector2(x, y);
      }
    }
  }

  return adjacentCells;
}

const std::map<CardinalDirection, Vector2> Vector2Operation::adjacentCellsMap(Vector2& pivot) {
  std::array<Vector2, 8> adjacentCellsArr = adjacentCellsArray(pivot);
  const std::map<CardinalDirection, Vector2> adjacentCellsMap {
		{ CardinalDirection::NORTH_WEST, adjacentCellsArr[0] },
		{ CardinalDirection::NORTH,			 adjacentCellsArr[1] },
		{ CardinalDirection::NORTH_EAST, adjacentCellsArr[2] },
		{ CardinalDirection::EAST,			 adjacentCellsArr[3] },
		{ CardinalDirection::SOUTH_EAST, adjacentCellsArr[4] },
		{ CardinalDirection::SOUTH, 		 adjacentCellsArr[5] },
		{ CardinalDirection::WEST, 			 adjacentCellsArr[6] },
		{ CardinalDirection::SOUTH_WEST, adjacentCellsArr[7] },
	};

  return adjacentCellsMap;
}
