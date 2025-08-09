#include "Playfield.hpp"

void Playfield::clearBoard()
{
	// TODO: Implement an iterator for Flat2DArray and replace this with a ranged loop to make the code cleaner and more efficient
	unsigned int totalCells = GameConfig::BOARD_WIDTH * GameConfig::BOARD_HEIGHT + GameConfig::BUFFER_ZONE;
	for (int y = 0; y < GameConfig::BOARD_WIDTH; y++)
		for (int x = 0; x < GameConfig::BOARD_HEIGHT; x++)
			m_PlayfieldMatrix(x, y).resetTile();
}

bool Playfield::isRowComplete(unsigned int row) const
{
	for (unsigned int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (m_PlayfieldMatrix(col, row).isEmpty()) return false;
	}
	return true;
}

bool Playfield::isRowEmpty(unsigned int row) const
{
	for (unsigned int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
		if (m_PlayfieldMatrix(col, row).isGrounded()) return false;
	}
	return true;
}

std::vector<unsigned int> Playfield::getCompletedRows() const
{
	std::vector<unsigned int> completedRows;
	for (unsigned int row = 0; row < GameConfig::BOARD_HEIGHT; row++) {
		if (isRowComplete(row)) completedRows.push_back(row);
	}
	return completedRows;
}

void Playfield::clearRows(const std::vector<unsigned int>& completedRows)
{
	for (const auto& row: completedRows)
	{
		for (unsigned int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
			m_PlayfieldMatrix(col, row).resetTile();
		}
	}

	for (unsigned int row = completedRows.back(); row > 0; row--)
	{
		int nextRow = row - 1;
		while (isRowEmpty(nextRow) && nextRow > -1) nextRow--;

		if (nextRow > -1)
		{
			for (unsigned int col = 0; col < GameConfig::BOARD_WIDTH; col++) {
				m_PlayfieldMatrix(col, row) = m_PlayfieldMatrix(col, nextRow);
			}
		}
		else break;
	}
}

// TODO: Finish the Tetromino class and come back to this
// bool Playfield::canPlacePiece(const Tetromino& piece, const Vector2& position) const {}

// void Playfield::placePiece(const Tetromino& piece, const Vector2& position) {}
