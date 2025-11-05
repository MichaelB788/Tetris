#include "util/vector2.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/tile-state.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Tetromino Operations", "[Matrix, Tetromino, unit]") 
{
	Matrix matrix;

	SECTION("Assigning a Tetromino in a invalid position")
	{
		Tetromino T = Tetromino(TetrominoType::T, {0, 0});
		REQUIRE_FALSE(matrix.assignActor(&T));
		T.shift(-999, -999);
		REQUIRE_FALSE(matrix.assignActor(&T));
	}

	SECTION("Assigning a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		REQUIRE(matrix.assignActor(&O));
	}

	SECTION("Grounding a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		CHECK(matrix.assignActor(&O));
		matrix.placeActor();
		matrix.groundActor();

		Tetromino T = Tetromino(TetrominoType::T, {5, 5});
		CHECK(matrix.assignActor(&T));
		REQUIRE(matrix.actorCollidesGround());
	}
}
