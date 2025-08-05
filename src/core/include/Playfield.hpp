#pragma once

#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <vector>

#include "GameConstants.hpp"
#include "Vector2.hpp"
#include "Flat2DArray.hpp"
#include "Tetromino.hpp"

/**
 * @file Playfield.hpp
 * @brief Defines the Matrix class for managing the Tetris game board state.
 */

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
	/**
	 * @brief Internal 2D array storing the board's tile states.
	 */
	Flat2DArray<Tile, GameConfig::BOARD_WIDTH, GameConfig::BOARD_HEIGHT + GameConfig::BUFFER_ZONE> m_PlayfieldMatrix;

	/**
	 * @brief Replaces a row in the playfield with another row.
	 * 
	 * @param replacedRow The index of the row to be replaced
	 * @param targetRow The index of the row to copy from
	 */
	void replaceRow(unsigned int replacedRow, unsigned int targetRow);

public:
	/**
	 * @brief Default constructor - initializes an empty board.
	 */
	Playfield() = default;

	/**
	 * @brief Clears the entire board, resetting all tiles to empty state.
	 */
	void clearBoard();

	/**
	 * @brief Checks if the tile at the given coordinate is occupied.
	 *
	 * @param coordinate The position to check (x, y coordinates)
	 * @return true if the tile is occupied (contains a Tetromino piece)
	 * @return false if the tile is empty
	 */
	bool isOccupied(const Vector2& coordinate) const { return m_PlayfieldMatrix(coordinate).isGrounded(); };

	/**
	 * @brief Retrieves the tile at the specified coordinate.
	 *
	 * @param coordinate The position to query (x, y coordinates)
	 * @return Tile The tile object at the given position
	 */
	const Tile& getTileAt(const Vector2& coordinate) const { return m_PlayfieldMatrix(coordinate); };

	/**
	 * @brief Sets the tile at the specified coordinate to a new value.
	 *
	 * @param coordinate The position to modify (x, y coordinates)
	 * @param newTile The new tile value to set at the position
	 */
	void setTileAt(const Vector2& coordinate, const Tile& newTile) { m_PlayfieldMatrix(coordinate) = newTile; };

	/**
	 * @brief Checks if an entire row is completely filled
	 * 
	 * @param row The row index to check
	 * @return true if all tiles in the row are occupied
	 */
	bool isRowComplete(unsigned int row) const;

	/**
	 * @brief Checks if an entire row is completely empty
	 * 
	 * @param row The row index to check
	 * @return true if all tiles in the row are empty
	 */
	bool isRowEmpty(unsigned int row) const;

	/**
	 * @brief Checks if any rows are completely filled and marks them for clearing
	 * 
	 * @return Vector of row indices that are complete
	 */
	std::vector<unsigned int> getCompletedRows() const;

	/**
	 * @brief Removes completed rows and drops rows above downward
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
	bool canPlacePiece(const Tetromino& piece, const Vector2& position) const;

	/**
	 * @brief Places a tetromino permanently on the board (locks it down)
	 * 
	 * @param piece The tetromino to place
	 * @param position The position to place it at
	 */
	void placePiece(const Tetromino& piece, const Vector2& position);
};