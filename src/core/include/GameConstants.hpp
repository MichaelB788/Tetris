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

enum class Type : uint8_t
{
	NONE = 0,
	I, O, T, Z, S, J, L
};

enum class Role : uint8_t
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
	Type type;
	Role role;

	Tile() : type(Type::NONE), role(Role::NONE) {}
	Tile(const Type& type, const Role& role) : type(type), role(role) {}

	bool isEmpty() const { return type == Type::NONE; }
	bool isGrounded() const { return role == Role::GROUNDED; }
	bool isActive() const { return role == Role::ACTIVE; }
	bool isGhost() const { return role == Role::GHOST; }
	void resetTile()
	{
		type = Type::NONE;
		role = Role::NONE;
	}
};

namespace GameConfig {
	static constexpr unsigned int BOARD_WIDTH = 10, BOARD_HEIGHT = 22;
};