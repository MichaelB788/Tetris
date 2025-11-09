#ifndef MATRIX_TILE_H
#define MATRIX_TILE_H
#include "core/tetromino.hpp"

struct MatrixTile {
	enum class State : uint8_t {
		EMPTY,
		ACTIVE,
		GHOST,
		GROUND,
		WALL,
	};

	State state = State::EMPTY;
	Tetromino::Type type = Tetromino::Type::NONE;

	constexpr MatrixTile() = default;
	constexpr MatrixTile(State ts) : state(ts) {};
	constexpr MatrixTile(State ts, Tetromino::Type tt) : state(ts), type(tt) {};

	inline constexpr bool isEmpty() const {
		return state == State::EMPTY
			|| state == State::ACTIVE
			|| state == State::GHOST;
	}
	inline constexpr bool isImpermiable() const {
		return state == State::WALL
			|| state == State::GROUND;
	}
	inline constexpr bool isGround() const { return state == State::GROUND; }

	inline void occupy(Tetromino::Type t) {
		state = State::ACTIVE;
		type = t;
	}
	inline void ground(Tetromino::Type t) {
		state = State::GROUND;
		type = t;
	}
	inline void occupyAsGhost(Tetromino::Type t) {
		state = State::GHOST;
		type = t;
	}
	inline void clear() {
		state = State::EMPTY;
		type = Tetromino::Type::NONE;
	}
};

#endif
