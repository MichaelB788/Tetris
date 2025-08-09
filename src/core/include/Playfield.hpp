#pragma once

#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <vector>

#include "GameConstants.hpp"
#include "Flat2DArray.hpp"

 /**
	* @class Playfield
	* @brief Manages the Tetris matrix (playfield) state and operations.
	* 
	* The playfield (known as the Matrix in the guideline) is 10 cells wide and 20 cells tall, with an additional 20 cell buffer zone above
	* the top of the playfield, usually hidden or obstructed by the field frame. A sliver of the 21st row is shown to aid players manipulate
	* the active piece in that area.
	*
	* The Playfield uses a coordinate system where (0,0) represents the top-left corner,
	* with x increasing rightward and y increasing downward.
	*/
class Playfield
{
private:
	Flat2DArray<Tile, GameConfig::BOARD_WIDTH, GameConfig::BOARD_HEIGHT + GameConfig::BUFFER_ZONE> m_PlayfieldMatrix;

public:
	Playfield() = default;

	void clearBoard();
	bool isOccupied(unsigned int x, unsigned int y) const { return m_PlayfieldMatrix(x, y).isGrounded(); };
	const Tile& getTileAt(unsigned int x, unsigned int y) const { return m_PlayfieldMatrix(x, y); };
	void setTileAt(unsigned int x, unsigned int y, const Tile& newTile) { m_PlayfieldMatrix(x, y) = newTile; };
	bool isRowComplete(unsigned int row) const;
	bool isRowEmpty(unsigned int row) const;

	/**
	 * @brief Searches the entire board and marks the rows which are completely filled, designed to be used with clearRows.
	 * 
	 * @return Vector of row indices that are complete
	 */
	std::vector<unsigned int> getCompletedRows() const;

	/**
	 * @brief Removes all rows from the playfield. Pulls any floating rows down to the row above the lowest populated row.
	 * 
	 * @param completedRows Vector of row indices to clear
	 */
	void clearRows(const std::vector<unsigned int>& completedRows);

	/**
	 * @brief Attempts to place a tetromino on the board
	 * 
	 * @param piece The tetromino to place
	 * @param position The position to place it at
	 * @return true if placement is valid and successful
	 */
	// bool canPlacePiece(const Tetromino& piece, const Vector2& position) const;

	/**
	 * @brief Places a tetromino permanently on the board (locks it down)
	 * 
	 * @param piece The tetromino to place
	 * @param position The position to place it at
	 */
	// void placePiece(const Tetromino& piece, const Vector2& position);
};