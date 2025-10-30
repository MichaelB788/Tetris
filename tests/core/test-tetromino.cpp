#include <catch2/catch_test_macros.hpp>
#include <array>
#include "util/vector2.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Moving Tetromino", "[tetromino_operation, unit]") {
	Tetromino tet = Tetromino();
	std::array<Vector2, 4> before = tet.coordinates();
	tet.shift(10, 10);
	for (int i = 0; i < 4; i++)
		REQUIRE(tet.coordinates()[i].x - before[i].x == 0);
}

TEST_CASE("Rotating a Tetromino", "[tetromino_operation, unit]") {
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(TetrominoType::O);
		std::array<Vector2, 4> before = O.coordinates();

		O.rotateClockwise();
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(O.coordinates()[i].x == before[i].x);
			REQUIRE(O.coordinates()[i].y == before[i].y);
		}
	}
}
