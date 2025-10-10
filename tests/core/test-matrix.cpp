#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "util/vector2.hpp"
#include "core/matrix.hpp"

TEST_CASE("Matrix indexing", "[Matrix, Vector2, unit]")
{
	Matrix matrix;

	SECTION("Vector2 indexing and integer indexing equals the same thing")
	{
		REQUIRE(matrix(0, 0) == matrix(Vector2(0, 0)));
	}

	SECTION("Walls are correctly positioned at 0 and MatrixWidth")

	SECTION("Out of bounds index returns TileState::INVALID")
	{
		REQUIRE(matrix(-100, -100) == TileState::INVALID);
		REQUIRE(matrix(1000, 1000) == TileState::INVALID);
		REQUIRE(matrix(MatrixDimensions::WIDTH, MatrixDimensions::HEIGHT) == TileState::INVALID);
	}
}

TEST_CASE("Matrix constructor", "[Matrix, Vector2, integration]")
{
	Matrix matrix;
	for (unsigned int y = 0; y < MatrixDimensions::HEIGHT; y++)
	{
		for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++)
		{
			INFO("Recorded at (" << x << ", " << y << ")")
				if (x == 0 || x == MatrixDimensions::WIDTH - 1)
				{
					REQUIRE(matrix(x, y) == TileState::WALL);
				}
				else if (y == MatrixDimensions::HEIGHT - 1)
				{
					REQUIRE(matrix(x, y) == TileState::GROUND);
				}
				else
				{
					REQUIRE(matrix(x, y) == TileState::EMPTY);
				}
		}
	}
}

TEST_CASE("Matrix Operations", "[Matrix, Vector2, unit]")
{
	Matrix matrix;

	SECTION("Clearing the board") {}
}
