#pragma once
#include <initializer_list>
#include <algorithm>

#include "GameConstants.hpp"
#include "Vector2.hpp"
#include "Flat2DArray.hpp"

/**
 *	@breif: The game board is a 10 x 20 grid of Tile which tracks the state of
 *  Tetromino.
 * 
 * The board should be responsible for checking the following: 
 * - Get and set tile states at specific coordinates
 * - Check if a position is valid/within bounds
 * - Clear the entire board or reset to an empty state
 * - Check if a tile is occupied or empty
 */ 
class Board
{
private:
	Flat2DArray<Tile, BoardDimension::WIDTH, BoardDimension::HEIGHT> m_State;

public:
	Board() = default;

	Tile getTileAt(const Vector2& coordinate) const { return m_State(coordinate.x, coordinate.y); }
	void setTileAt(const Vector2& coordinate, const Tile& newTile) const { m_State(coordinate.x, coordinate.y) = newTile; }

	bool isValidPosition(const Vector2& coordinate) const;
	bool isOccupied(const Vector2& coordinate) const;
	void clearBoard();
};
