#include "Playfield.hpp"

void Playfield::clearBoard()
{
	// TODO: Implement an iterator for Flat2DArray and replace this with a ranged loop to make the code cleaner
	// There's also the added bonus of not having to use m_PlayfieldMatrix[i] to access elements, which is not recommended.
	unsigned int totalCells = GameConfig::BOARD_WIDTH * GameConfig::BOARD_HEIGHT + GameConfig::BUFFER_ZONE;
	for (int i = 0; i < totalCells; i++) m_PlayfieldMatrix[i].resetTile();
}

bool Playfield::isRowComplete(unsigned int row) const
{
	Vector2 coordinate = Vector2(0, row);
	for (coordinate.x; coordinate.x < GameConfig::BOARD_WIDTH; coordinate.x++)
		if (m_PlayfieldMatrix(coordinate).isEmpty()) return false;
	return true;
}

bool Playfield::isRowEmpty(unsigned int row) const
{
	Vector2 coordinate = Vector2(0, row);
	for (coordinate.x; coordinate.x < GameConfig::BOARD_WIDTH; coordinate.x++)
		if (m_PlayfieldMatrix(coordinate).isGrounded()) return false;
	return true;
}

std::vector<unsigned int> Playfield::getCompletedRows() const
{
	std::vector<unsigned int> completedRows;
	for (unsigned int row = 0; row < GameConfig::BOARD_HEIGHT; row++)
		if (isRowComplete(row)) completedRows.push_back(row);
	return completedRows;
}

void Playfield::clearRows(const std::vector<unsigned int>& completedRows)
{
	// 1. Clear the rows from the vector first
	for (const auto& completedRow : completedRows)
	{
		Vector2 targetCoordinate = Vector2(0, completedRow);
		for (targetCoordinate.x; targetCoordinate.x < GameConfig::BOARD_WIDTH; targetCoordinate.x++)
			m_PlayfieldMatrix(targetCoordinate).resetTile();
	}

	// 2. Start from the last full row (which should be cleared at this point) 
	for (unsigned int currentRow = completedRows.back(); currentRow > 0; currentRow--)
	{
		unsigned int nextRow = currentRow - 1;
		// 3. Find the next available populated row, keep searching if it is not immediately found
		while (isRowEmpty(nextRow) || nextRow > -1) nextRow--;

		// 4. Once found, replace the current one with the one that was just found
		if (nextRow > -1) replaceRow(currentRow, nextRow);
		else break;
	}
}

// TODO: Finish the Tetromino class and come back to this
bool Playfield::canPlacePiece(const Tetromino& piece, const Vector2& position) const {}

void Playfield::placePiece(const Tetromino& piece, const Vector2& position) {}

void Playfield::replaceRow(unsigned int replacedRow, unsigned int targetRow)
{
	Vector2 coordinateOfReplaced = Vector2(0, replacedRow);
	Vector2 coordinateOfTarget = Vector2(0, targetRow);

	for (coordinateOfReplaced.x; coordinateOfReplaced.x < GameConfig::BOARD_WIDTH; coordinateOfReplaced.x++)
		m_PlayfieldMatrix(coordinateOfReplaced) = m_PlayfieldMatrix(coordinateOfTarget);
}
