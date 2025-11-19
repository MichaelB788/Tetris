#include "util/color.hpp"

const SDL_Color Color::getColor(const Color::ID color) {
	switch (color) {
		case Color::ID::WHITE:   return {255, 255, 255, 255};
		case Color::ID::BLUE:    return {0, 0, 255, 255};
		case Color::ID::RED:     return {255, 0, 0, 255};
		case Color::ID::GREEN:   return {0, 255, 0, 255};
		case Color::ID::CYAN:    return {0, 255, 255, 255};
		case Color::ID::ORANGE:  return {255, 165, 0, 255};
		case Color::ID::MAGENTA:  return {255, 60, 181, 255};
		case Color::ID::YELLOW:  return {255, 255, 0, 255};
		case Color::ID::GRAY:    return {128, 128, 128, 255};
		case Color::ID::BLACK: default:  return {0, 0, 0, 255};
	}
}

const SDL_Color Color::getTetrominoColor(const TetrominoType type) {
	switch (type) {
		case TetrominoType::I:  return getColor(ID::CYAN);
		case TetrominoType::O:  return getColor(ID::YELLOW);
		case TetrominoType::T:  return getColor(ID::MAGENTA);
		case TetrominoType::S:  return getColor(ID::GREEN);
		case TetrominoType::Z:  return getColor(ID::RED);
		case TetrominoType::J:  return getColor(ID::BLUE);
		case TetrominoType::L:  return getColor(ID::ORANGE);
		case TetrominoType::NONE: default:  return getColor(ID::WHITE);
	}
}

const SDL_Color Color::getMatrixTileColor(const MatrixTile tile) {
	switch (tile.state) {
		case MatrixTile::State::EMPTY: return getColor(ID::GRAY);
		case MatrixTile::State::WALL: return getColor(ID::WHITE);
		case MatrixTile::State::GHOST: default: return getTetrominoColor(tile.type);
	}
}
