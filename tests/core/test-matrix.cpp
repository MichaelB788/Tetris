#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/tile-state.hpp"
#include "core/matrix.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Matrix constructor", "[Matrix, unit]")
{
	Matrix matrix;

	SECTION("Walls are correctly placed at the start and end of each row")
	{
		for (unsigned int y = 0; y < matrix.HEIGHT; y++)
		{
			INFO("Checking coordinates at row " << y);
			REQUIRE(matrix.get(0, y).isImpermiable());
			REQUIRE(matrix.get(matrix.WIDTH - 1, y).isImpermiable());
		}
	}

	SECTION("Empty tiles fill up space between each wall")
	{
		for (unsigned int y = 0; y < matrix.HEIGHT; y++)
		{
			for (unsigned int x = 1; x < matrix.WIDTH - 1; x++)
			{
				INFO("Checking coordinates at row " << x << ", " << y);
				REQUIRE(matrix.get(x, y).isEmpty());
			}
		}
	}
}

TEST_CASE("Placing Tetromino", "[Matrix, Tetromino, unit]") 
{
	Matrix matrix;

	SECTION("Placing a Tetromino in a invalid position")
	{
		Tetromino t;
	}
}
