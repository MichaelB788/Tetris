#ifndef MATRIX_TILE_H
#define MATRIX_TILE_H
#include "core/tetromino.hpp"

struct Tile {
	enum class State : uint8_t {
		EMPTY,
		ACTIVE,
		GHOST,
		GROUND,
		WALL,
	};

	State state;
	Tetromino::Type type;

	constexpr Tile(State state = Tile::State::EMPTY, Tetromino::Type type = Tetromino::Type::NONE)
		: state(state),
			type(type)
	{};

	bool isEmpty() const {
		return state == State::EMPTY || state == State::ACTIVE || state == State::GHOST;
	}

	bool isImpermiable() const {
		return state == State::WALL || state == State::GROUND;
	}

	void setActive(Tetromino::Type t) {
		state = State::ACTIVE;
		type = t;
	}

	void setGround(Tetromino::Type t) {
		state = State::GROUND;
		type = t;
	}

	void setGhost(Tetromino::Type t) {
		state = State::GHOST;
		type = t;
	}

	void clear() {
		state = State::EMPTY;
		type = Tetromino::Type::NONE;
	}
};

#endif
