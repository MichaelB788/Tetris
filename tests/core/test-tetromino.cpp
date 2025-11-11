#include <catch2/catch_test_macros.hpp>
#include "util/vector2.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Moving Tetromino", "[Tetromino, unit]") {
	Tetromino tet = Tetromino({0, 0});
	Tetromino before = tet;

	Vector2 translation = {10, 10};

	tet.shift(translation);

	auto beforeIt = before.begin();
	for (auto& block : tet) {
		REQUIRE(block == *beforeIt + translation);
		beforeIt++;
	}
}

TEST_CASE("Tetromino Rotation", "[Tetromino, unit]") {
	SECTION("Counterclockwise rotations not the same as clockwise") {
		Tetromino firstTetromino = {TetrominoType::S, {40, 79}};
		Tetromino secondTetromino = firstTetromino;

		firstTetromino.rotate(Direction::Rotation::CLOCKWISE);
		secondTetromino.rotate(Direction::Rotation::COUNTERCLOCKWISE);

		bool clockwiseEqualsCounterclockwise = true;
		auto secondTetrominoIt = secondTetromino.begin();
		for (const auto& block : firstTetromino) {
			if (block != *secondTetrominoIt) clockwiseEqualsCounterclockwise = false;
			secondTetrominoIt++;
		}

		REQUIRE_FALSE(clockwiseEqualsCounterclockwise);
	}
}
