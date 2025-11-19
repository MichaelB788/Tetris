#ifndef MATRIX_TILE_H
#define MATRIX_TILE_H
#include "core/tetromino-type.hpp"

struct MatrixTile {
	enum class State : uint8_t {
		EMPTY,
		ACTIVE,
		GHOST,
		GROUND,
		WALL,
	};

	State state = State::EMPTY;
	TetrominoType type = TetrominoType::NONE;

	constexpr MatrixTile() = default;
	constexpr MatrixTile(State ts) : state(ts) {};
	constexpr MatrixTile(State ts, TetrominoType tt) : state(ts), type(tt) {};

	bool isEmpty() const {
		return state == State::EMPTY || state == State::ACTIVE || state == State::GHOST;
	}

	bool isImpermiable() const {
		return state == State::WALL || state == State::GROUND;
	}

	void setActive(TetrominoType t) {
		state = State::ACTIVE;
		type = t;
	}

	void setGround(TetrominoType t) {
		state = State::GROUND;
		type = t;
	}

	void setGhost(TetrominoType t) {
		state = State::GHOST;
		type = t;
	}

	void clear() {
		state = State::EMPTY;
		type = TetrominoType::NONE;
	}
};

#endif
