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
		REQUIRE_FALSE(matrix.actorIsWithinBounds(T));
		T.shift(-999, -999);
		REQUIRE_FALSE(matrix.actorIsWithinBounds(T));
	}

	SECTION("Assigning a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		REQUIRE(matrix.actorIsWithinBounds(O));
	}

	SECTION("Grounding a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		CHECK(matrix.actorIsWithinBounds(O));
		matrix.placeActor(O);
		matrix.groundActor(O);

		Tetromino T = Tetromino(TetrominoType::T, {5, 5});
		CHECK(matrix.actorIsWithinBounds(T));
		REQUIRE(matrix.actorCollidesGround(T));
	}
}
