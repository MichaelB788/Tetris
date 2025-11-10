#include "util/vector2.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Tetromino Operations", "[Matrix, Tetromino, unit]") 
{
	Matrix matrix;

	SECTION("Assigning a Tetromino in a invalid position")
	{
		Tetromino T = Tetromino(TetrominoType::T, {0, 0});
		REQUIRE(matrix.tetrominoIsOutOfBounds(T));
		T.shift(-999, -999);
		REQUIRE(matrix.tetrominoIsOutOfBounds(T));
	}

	SECTION("Assigning a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		REQUIRE_FALSE(matrix.tetrominoIsOutOfBounds(O));
	}

	SECTION("Grounding a Tetromino in a valid position")
	{
		Tetromino O = Tetromino(TetrominoType::O, {5, 5});
		CHECK_FALSE(matrix.tetrominoIsOutOfBounds(O));
		matrix.assignActor(&O);
		matrix.groundActor();

		Tetromino T = Tetromino(TetrominoType::T, {5, 5});
		CHECK_FALSE(matrix.tetrominoIsOutOfBounds(T));
		matrix.assignActor(&T);
		REQUIRE(matrix.actorCollidesGround());
	}
}

TEST_CASE("Line operations") {
	Matrix matrix;
	matrix(5, 5).ground(TetrominoType::T);
}
