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
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(TetrominoType::O, {0, 0});
		Tetromino before = O;

		O.rotate(Vector2::Rotation::CLOCKWISE);

		auto beforeIt = before.begin();
		for (auto& block : O) {
			REQUIRE(block == *beforeIt);
			beforeIt++;
		}
	}

	SECTION("Counterclockwise rotations not the same as clockwise") {
		Tetromino firstTetromino = {{40, 79}};
		Tetromino secondTetromino = firstTetromino;

		firstTetromino.rotate(Vector2::Rotation::CLOCKWISE);
		secondTetromino.rotate(Vector2::Rotation::COUNTERCLOCKWISE);

		bool allEqual = true;
		auto secondTetrominoIt = secondTetromino.begin();
		for (auto block : firstTetromino) {
			if (block != *secondTetrominoIt) allEqual = false;
			secondTetrominoIt++;
		}

		INFO("All coordinates resulting from a counterclockwise and a clockwise rotation of the same Tetromino found to be equal.");
		REQUIRE_FALSE(allEqual);
	}

	SECTION("Counterclockwise rotation followed by clockwise") {
		Tetromino tetromino = {{32, 75}};
		Tetromino before = tetromino;

		tetromino.rotate(Vector2::Rotation::CLOCKWISE);
		tetromino.rotate(Vector2::Rotation::COUNTERCLOCKWISE);

		auto beforeIt = before.begin();
		for (auto& block : tetromino) {
			REQUIRE(block == *beforeIt);
		}
	}
}

TEST_CASE("Assignment operator", "[Tetromino, unit]") {
	SECTION("Overriding previous assignment") {
		Tetromino T {TetrominoType::T, {0, 0}};
		Tetromino O {TetrominoType::O, {-99, -99}};

		O = T;

		REQUIRE(O.type() == T.type());

		auto TIter = T.begin();
		for (const auto& block : O) {
			REQUIRE(block == *TIter);
			TIter++;
		}
	}
}
