/**
 * @file GameConstants.hpp
 * @brief Core constants, enumerations, and data structures for the Tetris game.
 *
 * This file defines all the fundamental game constants, state enumerations,
 * and the basic Tile structure used throughout the Tetris implementation.
 */

#pragma once

 /**
	* @enum Direction
	* @brief Represents possible movement directions for Tetromino pieces.
	*/
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

/**
 * @enum GameState
 * @brief Represents the current state of the game session.
 */
enum class GameState { RUNNING, GAME_OVER, PAUSED, EXIT };

/**
 * @enum TetrominoType
 * @brief Identifies the seven standard Tetromino, plus empty state.
 */
enum class TetrominoType { I, O, T, Z, S, J, L, NONE };

/**
 * @enum TileState
 * @brief Represents the current state of a tile on the game board.
 */
enum class TileState { FALLING, GROUNDED, EMPTY };

/**
 * @struct Tile
 * @brief Represents a single tile on the game board.
 */
struct Tile
{
	TetrominoType m_Type;
	TileState m_State;

	/**
	 * @brief Default constructor - creates an empty tile with no type.
	 */
	Tile() : m_Type(TetrominoType::NONE), m_State(TileState::EMPTY) {}

	/**
	 * @brief Parameterized constructor - creates a tile with specified type and state.
	 *
	 * @param type The piece type for this tile
	 * @param state The initial state for this tile
	 */
	Tile(const TetrominoType& type, const TileState& state) : m_Type(type), m_State(state) {}

	/**
	 * @brief Resets the tile to its default empty state.
	 */
	void resetTile()
	{
		m_Type = TetrominoType::NONE;
		m_State = TileState::EMPTY;
	}

	/**
	 * @brief Checks if the current tile is empty.
	 */
	bool isEmpty() const { return m_State == TileState::EMPTY; }

	/**
	 * @brief Checks if the current tile is empty.
	 */
	bool isGrounded() const { return m_State == TileState::GROUNDED; }
};

struct GameConfig {
public:
  /** 
	 * @brief The height and width of the Tetris playfield in tiles.
	 *
   * The vast majority of tetromino based games use a playfield 10 cells wide and between 16 and 24 cells tall, with most Guideline-based games using a visible height of 20 cells.
   */
	static constexpr unsigned int BOARD_WIDTH = 10, BOARD_HEIGHT = 20, BUFFER_ZONE = 2;
};