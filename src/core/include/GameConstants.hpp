#pragma once

enum class Direction { LEFT, RIGHT, DOWN };

/**
 * @enum Difficulty
 *
 * @brief Game difficulty levels defined by drop interval in milliseconds.
 * @note These may need to be tweaked as it uses magic numbers.
 */
enum class Difficulty {
	EASY = 200,     ///< Easy mode - 200ms between drops
	NORMAL = 100,   ///< Normal mode - 100ms between drops
	HARD = 50       ///< Hard mode - 50ms between drops
};

enum class GameState { RUNNING, GAME_OVER, PAUSED, EXIT };

enum class TetrominoType { I, O, T, Z, S, J, L, NONE };

enum class TileState { FALLING, GROUNDED, EMPTY, STORED };

/**
 * @brief Represents a single tile in the Tetris playfield.
 * Each tile can be empty or occupied by a part of a Tetromino.
 */
struct Tile
{
	TetrominoType type;
	TileState state;

	Tile() : type(TetrominoType::NONE), state(TileState::EMPTY) {}
	Tile(const TetrominoType& type, const TileState& state) : type(type), state(state) {}

	bool isEmpty() const { return state == TileState::EMPTY; }
	bool isGrounded() const { return state == TileState::GROUNDED; }
	void resetTile()
	{
		type = TetrominoType::NONE;
		state = TileState::EMPTY;
	}
};

namespace GameConfig {
	static constexpr unsigned int BOARD_WIDTH = 10, BOARD_HEIGHT = 20, BUFFER_ZONE = 2;
};