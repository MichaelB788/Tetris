#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "util/vector2.hpp"
#include "core/matrix.hpp"

TEST_CASE("Matrix indexing", "[Matrix, Vector2, unit]")
{
	Matrix matrix;

	SECTION("Vector2 and integer indexing")
	{
		REQUIRE(matrix(0, 0) == matrix(Vector2(0, 0)));
		REQUIRE_FALSE(matrix(0, 1) == matrix(Vector2(1, 0)));
	}

	SECTION("operator() overrides")
	{
		INFO("Assigning (10, 10) with an active tile");
		matrix(Vector2(10, 10)) = TileState::ACTIVE;
		REQUIRE(matrix(10, 10) == TileState::ACTIVE);
	}
}

TEST_CASE("Matrix constructor", "[Matrix, Vector2, integration]")
{
	Matrix matrix;

	SECTION("Walls are correctly placed at the start and end of each row")
	{
		for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++)
		{
			INFO("Checking coordinates at row " << y);
			REQUIRE(matrix(0, y) == TileState::WALL);
			REQUIRE(matrix(matrix_dimensions::WIDTH - 1, y) == TileState::WALL);
		}
	}

	SECTION("Empty tiles fill up space between each wall")
	{
		for (unsigned int y = 0; y < matrix_dimensions::HEIGHT; y++)
		{
			for (unsigned int x = 1; x < matrix_dimensions::WIDTH - 1; x++)
			{
				INFO("Checking coordinates at row " << x << ", " << y);
				REQUIRE(matrix(x, y) == TileState::EMPTY);
			}
		}
	}
}
