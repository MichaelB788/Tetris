#include "core/tetromino.hpp"
#include <random>

Tetromino::Type Tetromino::getRandomType(std::mt19937& gen) {
	static constexpr std::array<Type, 7> types { Type::I, Type::O, Type::T, Type::Z, Type::S, Type::J, Type::L };

	static std::uniform_int_distribution<> distrib(0, types.size() - 1);
	return types[distrib(gen)];
}

void Tetromino::shift(int dx, int dy) {
	for (auto& block : blocks) {
		block.x += dx;
		block.y += dy;
	}
}

void Tetromino::move(int x, int y) {
	int dx = x - blocks[0].x;
	int dy = y - blocks[0].y;

	for (auto& block : blocks) {
		block.x += dx;
		block.y += dy;
	}
}

void Tetromino::rotate(Direction::Rotation direction) {
	if (type != Tetromino::Type::O) {
		for (int i = 1; i < 4; i++) {
			blocks[i].rotate90Degrees(direction, blocks[0]);
		}
		updateRotationState(direction);
	}
}

void Tetromino::updateRotationState(Direction::Rotation direction) {
	if ( direction == Direction::Rotation::CLOCKWISE ) {
		state = (state + 1) % 4;
	} else {
		state = (state - 1 < 0) ? 3 : state - 1;
	}
}

Tetromino::Blocks Tetromino::generateShape(Type type) {
	using v2 = Vector2;
	switch(type) {
		case Type::I: return { v2( 0,  0), v2(-1,  0), v2( 1,  0), v2( 2,  0) };
		case Type::O: return { v2( 0,  0), v2( 1,  0), v2( 0,  1), v2( 1,  1) };
		case Type::T: return { v2( 0,  0), v2(-1,  0), v2( 1,  0), v2( 0, -1) };
		case Type::Z: return { v2( 0,  0), v2(-1, -1), v2( 0, -1), v2( 1,  0) };
		case Type::S: return { v2( 0,  0), v2(-1,  0), v2( 0, -1), v2( 1, -1) };
		case Type::J: return { v2( 0,  0), v2(-1, -1), v2(-1,  0), v2( 1,  0) };
		case Type::L: return { v2( 0,  0), v2( 1, -1), v2( 1,  0), v2(-1,  0) };
		case Type::NONE: default: return { v2( 0,  0), v2( 0,  0), v2( 0,  0), v2( 0,  0) };
	};
}
