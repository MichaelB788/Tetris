#ifndef TILE_STATE_H
#define TILE_STATE_H
#include <stdint.h>
#include <optional>

enum class TetrominoType : uint8_t { I, O, T, Z, S, J, L };

enum class TileState : uint8_t {
	EMPTY,
	ACTIVE,
	GHOST,
	GROUND,
	WALL,
};

struct MatrixTile {
	TileState state = TileState::EMPTY;
	std::optional<TetrominoType> type = std::nullopt;

	constexpr MatrixTile() = default;
	constexpr MatrixTile(TileState ts) : state(ts) {};
	constexpr MatrixTile(TileState ts, TetrominoType tt) : state(ts), type(tt) {};

	inline constexpr bool isEmpty() const { return state == TileState::EMPTY; }
	inline constexpr bool isGround() const { return state == TileState::GROUND; }
	inline constexpr bool isImpermiable() const { return state == TileState::GROUND || state == TileState::WALL; }

	inline void occupy(TetrominoType t) {
		state = TileState::ACTIVE;
		type = t;
	}
	inline void clear() {
		state = TileState::EMPTY;
		type = std::nullopt;
	}
	inline void ground() { if (type.has_value()) state = TileState::GROUND; }
};

#endif
