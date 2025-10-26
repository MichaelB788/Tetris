#include <catch2/catch.hpp>
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-operations.hpp"

TEST_CASE("Moving Tetromino", "[tetromino_operation, unit]") {
	SECTION("Moving an I piece LEFT") {
		Tetromino I = Tetromino(TetrominoType::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.coordinates();

		I.moveLeft();
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.coordinates()[i].x == before[i].x - 1);
			REQUIRE(I.coordinates()[i].y == before[i].y);
		}
	}
	SECTION("Moving an I piece RIGHT") {
		Tetromino I = Tetromino(TetrominoType::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.coordinates();

		I.moveRight();
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.coordinates()[i].x == before[i].x + 1);
			REQUIRE(I.coordinates()[i].y == before[i].y);
		}
	}
	SECTION("Moving an I piece DOWN") {
		Tetromino I = Tetromino(TetrominoType::I, Vector2(0, 0));
		std::array<Vector2, 4> before = I.coordinates();

		I.moveDown();
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(I.coordinates()[i].x == before[i].x);
			REQUIRE(I.coordinates()[i].y == before[i].y + 1);
		}
	}
}

TEST_CASE("Rotating a Tetromino 90 Degrees Counterclockwise", "[tetromino_operation, unit]") {
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(TetrominoType::O, Vector2(0, 0));
		std::array<Vector2, 4> before = O.coordinates();

		O.rotateClockwise();
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(O.coordinates()[i].x == before[i].x);
			REQUIRE(O.coordinates()[i].y == before[i].y);
		}
	}
}
