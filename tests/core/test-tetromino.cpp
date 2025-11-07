#include <catch2/catch_test_macros.hpp>
#include <array>
#include "util/vector2.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Moving Tetromino", "[Tetromino, unit]") {
	Tetromino tet = Tetromino({0, 0});
	std::array<Vector2, 4> before = tet.coordinates();
	Vector2 translation{10, 10};

	tet.shift(translation);

	for (int i = 0; i < before.size(); i++) {
		REQUIRE(tet.coordinates()[i] - before[i] == translation);
	}
}

TEST_CASE("Tetromino Rotation", "[Tetromino, unit]") {
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(TetrominoType::O, {0, 0});
		std::array<Vector2, 4> before = O.coordinates();

		O.rotateClockwise();

		for (unsigned int i = 0; i < before.size(); i++) {
			REQUIRE(O.coordinates()[i] == before[i]);
		}
	}

	SECTION("Counterclockwise rotations not the same as clockwise") {
		Tetromino T1 = {{0, 0}};
		Tetromino T2 = T1;

		T1.rotateClockwise();
		T2.rotateCounterclockwise();

		bool allEqual = true;
		for (unsigned int i = 0; i < T1.coordinates().size(); i++) {
			if (T1.coordinates()[i] != T2.coordinates()[i]) {
				allEqual = false;
			}
		}

		INFO("All coordinates resulting from a counterclockwise and a clockwise rotation of the same Tetromino found to be equal.");
		REQUIRE_FALSE(allEqual);
	}

	SECTION("Counterclockwise rotation followed by clockwise") {
		Tetromino tetromino = {{0, 0}};
		std::array<Vector2, 4> before = tetromino.coordinates();

		tetromino.rotateClockwise();
		tetromino.rotateCounterclockwise();

		for (unsigned int i = 0; i < before.size(); i++) {
			REQUIRE(tetromino.coordinates()[i] == before[i]);
		}
	}
}

TEST_CASE("Assignment operator", "[Tetromino, unit]") {
	SECTION("Overriding previous assignment") {
		Tetromino T {TetrominoType::T, {0, 0}};
		Tetromino O {TetrominoType::O, {-99, -99}};
		CHECK_FALSE(O.type() == T.type());
		CHECK_FALSE(O.coordinates()[0] == T.coordinates()[0]);

		O = T;

		REQUIRE(O.type() == T.type());
		REQUIRE(O.coordinates()[0] == T.coordinates()[0]);
	}
}
