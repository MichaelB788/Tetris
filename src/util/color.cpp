#include "util/color.hpp"

const SDL_Color Color::getColor(const Color::ID color) {
	using ID = Color::ID;
	switch (color) {
		case ID::WHITE:   return {255, 255, 255, 255};
		case ID::BLUE:    return {0, 0, 255, 255};
		case ID::RED:     return {255, 0, 0, 255};
		case ID::GREEN:   return {0, 255, 0, 255};
		case ID::CYAN:    return {0, 255, 255, 255};
		case ID::ORANGE:  return {255, 165, 0, 255};
		case ID::MAGENTA:  return {255, 60, 181, 255};
		case ID::YELLOW:  return {255, 255, 0, 255};
		case ID::GRAY:    return {128, 128, 128, 255};
		case ID::BLACK: default:  return {0, 0, 0, 255};
	}
}

const SDL_Color Color::getTetrominoColor(const Tetromino::Type type) {
	using Type = Tetromino::Type;
	switch (type) {
		case Type::I:  return getColor(ID::CYAN);
		case Type::O:  return getColor(ID::YELLOW);
		case Type::T:  return getColor(ID::MAGENTA);
		case Type::S:  return getColor(ID::GREEN);
		case Type::Z:  return getColor(ID::RED);
		case Type::J:  return getColor(ID::BLUE);
		case Type::L:  return getColor(ID::ORANGE);
		case Type::NONE: default:  return getColor(ID::WHITE);
	}
}

const SDL_Color Color::getMatrixTileColor(const Tile tile) {
	using State = Tile::State;
	switch (tile.state) {
		case State::EMPTY: return getColor(ID::GRAY);
		case State::WALL: return getColor(ID::WHITE);
		case State::GHOST: default: return getTetrominoColor(tile.type);
	}
}
