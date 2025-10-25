#include <catch2/catch.hpp>
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/matrix-operations.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Placing, removing, and verifying placement of tiles in Matrix", "[matrix_operation, unit]")
{
	Matrix mat;
	constexpr unsigned int FILLED_ROW = 0;
	constexpr unsigned int UNFILLED_ROW = 1;

	SECTION("Full rows of active tiles should be ignored")
	{
		matrix_operation::fillRow(mat, TileState::ACTIVE, UNFILLED_ROW);
		REQUIRE_FALSE(matrix_operation::rowIsComplete(mat, UNFILLED_ROW));
	}

	SECTION("Full rows of ground tiles should be complete")
	{
		matrix_operation::fillRow(mat, TileState::GROUND, FILLED_ROW);
		REQUIRE(matrix_operation::rowIsComplete(mat, FILLED_ROW));
	}

	SECTION("Completed rows that are cleared should be empty")
	{
		matrix_operation::clearRow(mat, FILLED_ROW);
		INFO("Filled row was cleared");
		REQUIRE(matrix_operation::rowIsEmpty(mat, FILLED_ROW));
	}
}

TEST_CASE("Clearing the entire Matrix", "[matrix_operation, integration]")
{
	Matrix mat;

	SECTION("Filling one row and clearing the board")
	{
		matrix_operation::fillRow(mat, TileState::GROUND, 10);
		CHECK(matrix_operation::rowIsComplete(mat, 10));

		matrix_operation::clear(mat);
		REQUIRE(matrix_operation::rowIsEmpty(mat, 10));
	}
}

TEST_CASE("Tetromino placement, removal, and verification in Matrix", "[matrix_operation, Tetromino, unit]")
{
	Matrix mat;

	SECTION("Checking placement of Tetromino in invalid coordinates")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(0, 0));
		REQUIRE_FALSE(matrix_operation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Should not be able to place Tetromino out of bounds")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(-1000, -1000));
		REQUIRE_FALSE(matrix_operation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Should not be able to place Tetromino indexed exactly at matrix_dimensions::WIDTH or matrix_dimensions::HEIGHT")
	{
		Tetromino tet = Tetromino(Tetromino::Type::O, Vector2(matrix_dimensions::WIDTH, 5));
		REQUIRE_FALSE(matrix_operation::canPlaceTetromino(tet.m_coordinates, mat));

		Tetromino tet2 = Tetromino(Tetromino::Type::O, Vector2(0, matrix_dimensions::HEIGHT));
		REQUIRE_FALSE(matrix_operation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Checking placement of Tetromino in valid coordinates")
	{
		Tetromino tet = Tetromino(Tetromino::Type::O, Vector2(6, 6));
		REQUIRE(matrix_operation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Placing Tetromino I at row 6") 
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(1, 6));
		matrix_operation::placeTetromino(tet.m_coordinates, mat);
		REQUIRE_FALSE(matrix_operation::rowIsEmpty(mat, 6));
	}

	SECTION("Removing Tetromino I at row 6")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(1, 6));
		matrix_operation::removeTetromino(tet.m_coordinates, mat);
		REQUIRE(matrix_operation::rowIsEmpty(mat, 6));
	}
}

TEST_CASE("Dropping floating tiles in a Matrix", "[matrix_operation, unit]")
{
	SECTION("Dropping two consecutive floating rows")
	{
		Matrix mat;
		matrix_operation::fillRow(mat, TileState::GROUND, 0);
		matrix_operation::fillRow(mat, TileState::GROUND, 1);

		CHECK_FALSE(matrix_operation::rowIsEmpty(mat, 0));
		CHECK_FALSE(matrix_operation::rowIsEmpty(mat, 1));

		matrix_operation::dropFloatingRows(mat);

		INFO("Could not drop rows");
		REQUIRE_FALSE(matrix_operation::rowIsEmpty(mat, matrix_dimensions::HEIGHT - 1));
		REQUIRE_FALSE(matrix_operation::rowIsEmpty(mat, matrix_dimensions::HEIGHT - 2));

		INFO("Could not clear rows original position")
		REQUIRE(matrix_operation::rowIsEmpty(mat, 0));
		REQUIRE(matrix_operation::rowIsEmpty(mat, 1));
	}
}

TEST_CASE("Clearing completed rows", "[matrix_operation, unit]")
{
	Matrix mat;

	SECTION("Clearing two consecutive rows")
	{
		matrix_operation::fillRow(mat, TileState::GROUND, 0);
		matrix_operation::fillRow(mat, TileState::GROUND, 1);

		CHECK_FALSE(matrix_operation::rowIsEmpty(mat, 0));
		CHECK_FALSE(matrix_operation::rowIsEmpty(mat, 1));

		matrix_operation::clearCompletedRows(mat);
		REQUIRE(matrix_operation::rowIsEmpty(mat, 0));
		REQUIRE(matrix_operation::rowIsEmpty(mat, 1));
	}
}
