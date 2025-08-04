#include <array>
#include <cstdio>

#include "Board.hpp"

void Board::clearBoard()
{
		for (unsigned int y = 0; y < BoardDimension::HEIGHT; ++y)
		{
			for (unsigned int x = 0; x < BoardDimension::WIDTH; ++x)
			{
				m_State(x, y) = Tile::Empty;
			}
		}
}

// TODO: Implement the isValidPosition and isOccupied methods
bool Board::isValidPosition(const Vector2& coordinate) const
{
	return coordinate.x >= 0 && coordinate.x < BoardDimension::WIDTH &&
				 coordinate.y >= 0 && coordinate.y < BoardDimension::HEIGHT &&
}

bool Board::isOccupied(const Vector2& coordinate) const
{
}
