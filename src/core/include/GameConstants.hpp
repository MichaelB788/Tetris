#pragma once
#include <stdint.h>

enum class Direction : uint8_t
{
	LEFT,
	RIGHT,
	DOWN
};

enum class Difficulty : uint8_t
{
	EASY,
	NORMAL,
	HARD
};

enum class GameState : uint8_t
{
	RUNNING,
	GAME_OVER,
	PAUSED,
	EXIT
};

enum class TileType : uint8_t
{
	NONE = 0,
	I, O, T, Z, S, J, L
};

enum class TileRole : uint8_t
{
	NONE = 0,
	ACTIVE, GROUNDED, GHOST
};

/**
 * @brief Represents a single tile in the Tetris playfield.
 * Each tile can be empty or occupied by a part of a Tetromino.
 */
struct Tile
{
	TileType type;
	TileRole role;

	Tile() : type(TileType::NONE), role(TileRole::NONE) {}
	Tile(const TileType& type, const TileRole& role) : type(type), role(role) {}

	bool isEmpty() const { return type == TileType::NONE; }
	bool isGrounded() const { return role == TileRole::GROUNDED; }
	bool isActive() const { return role == TileRole::ACTIVE; }
	bool isGhost() const { return role == TileRole::GHOST; }
	void resetTile()
	{
		type = TileType::NONE;
		role = TileRole::NONE;
	}
};

namespace GameConfig {
	static constexpr unsigned int BOARD_WIDTH = 10, BOARD_HEIGHT = 20, BUFFER_ZONE = 2;
};