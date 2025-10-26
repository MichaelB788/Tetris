#include <catch2/catch.hpp>
#include <array>
#include "util/game-constants.hpp"
#include "util/vector2.hpp"
#include "core/tetromino.hpp"
#include "core/tetromino-operations.hpp"

TEST_CASE("Moving Tetromino", "[tetromino_operation, unit]") {
	Tetromino tet = Tetromino(TetrominoType::I, Vector2(0, 0));
	std::array<Vector2, 4> before = tet.coordinates();
	tet.move(-999, -999);
	REQUIRE(tet.coordinates()[0].x + before[0].x == -999);
}

TEST_CASE("Rotating a Tetromino", "[tetromino_operation, unit]") {
	SECTION("Rotating an O piece should not be possible") {
		Tetromino O = Tetromino(TetrominoType::O, Vector2(0, 0));
		std::array<Vector2, 4> before = O.coordinates();

		O.rotate(true);
		for (unsigned int i = 0; i < 4; i++) {
			REQUIRE(O.coordinates()[i].x == before[i].x);
			REQUIRE(O.coordinates()[i].y == before[i].y);
		}
	}
}
