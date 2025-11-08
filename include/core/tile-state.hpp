#ifndef TILE_STATE_H
#define TILE_STATE_H
#include <stdint.h>

enum class TetrominoType : int8_t { NONE = -1, I, O, T, Z, S, J, L };

enum class TileState : uint8_t {
	EMPTY,
	ACTIVE,
	GHOST,
	GROUND,
	WALL,
};

struct MatrixTile {
	TileState state = TileState::EMPTY;
	TetrominoType type = TetrominoType::NONE;

	constexpr MatrixTile() = default;
	constexpr MatrixTile(TileState ts) : state(ts) {};
	constexpr MatrixTile(TileState ts, TetrominoType tt) : state(ts), type(tt) {};

	inline constexpr bool isEmpty() const {
		return state == TileState::EMPTY
				|| state == TileState::ACTIVE
				|| state == TileState::GHOST;
	}
	inline constexpr bool isImpermiable() const {
		return state == TileState::WALL
				|| state == TileState::GROUND;
	}
	inline constexpr bool isGround() const { return state == TileState::GROUND; }

	inline void occupy(TetrominoType t) {
		state = TileState::ACTIVE;
		type = t;
	}
	inline void ground(TetrominoType t) {
		state = TileState::GROUND;
		type = t;
	}
	inline void occupyAsGhost(TetrominoType t) {
		state = TileState::GHOST;
		type = t;
	}
	inline void clear() {
		state = TileState::EMPTY;
		type = TetrominoType::NONE;
	}
};

#endif
