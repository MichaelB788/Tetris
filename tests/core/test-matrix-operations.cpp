#include <catch2/catch.hpp>
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/matrix-operations.hpp"
#include "core/tetromino.hpp"

TEST_CASE("Placing, removing, and verifying placement of tiles in Matrix", "[MatrixOperation, unit]")
{
	Matrix mat;
	constexpr unsigned int FILLED_ROW = 0;
	constexpr unsigned int UNFILLED_ROW = 1;

	SECTION("Full rows of active tiles should be ignored")
	{
		MatrixOperation::fillRow(mat, TileState::ACTIVE, UNFILLED_ROW);
		REQUIRE_FALSE(MatrixOperation::rowIsComplete(mat, UNFILLED_ROW));
	}

	SECTION("Full rows of ground tiles should be complete")
	{
		MatrixOperation::fillRow(mat, TileState::GROUND, FILLED_ROW);
		REQUIRE(MatrixOperation::rowIsComplete(mat, FILLED_ROW));
	}

	SECTION("Completed rows that are cleared should be empty")
	{
		MatrixOperation::clearRow(mat, FILLED_ROW);
		INFO("Filled row was cleared");
		REQUIRE(MatrixOperation::rowIsEmpty(mat, FILLED_ROW));
	}
}

TEST_CASE("Clearing the entire Matrix", "[MatrixOperation, integration]")
{
	Matrix mat;

	SECTION("Filling one row and clearing the board")
	{
		MatrixOperation::fillRow(mat, TileState::GROUND, 10);
		CHECK(MatrixOperation::rowIsComplete(mat, 10));

		MatrixOperation::clear(mat);
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 10));
	}
}

TEST_CASE("Tetromino placement, removal, and verification in Matrix", "[MatrixOperation, Tetromino, unit]")
{
	Matrix mat;

	SECTION("Checking placement of Tetromino in invalid coordinates")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(0, 0));
		REQUIRE_FALSE(MatrixOperation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Should not be able to place Tetromino out of bounds")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(-1000, -1000));
		REQUIRE_FALSE(MatrixOperation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Should not be able to place Tetromino indexed exactly at MatrixDimensions::WIDTH or MatrixDimensions::HEIGHT")
	{
		Tetromino tet = Tetromino(Tetromino::Type::O, Vector2(MatrixDimensions::WIDTH, 5));
		REQUIRE_FALSE(MatrixOperation::canPlaceTetromino(tet.m_coordinates, mat));

		Tetromino tet2 = Tetromino(Tetromino::Type::O, Vector2(0, MatrixDimensions::HEIGHT));
		REQUIRE_FALSE(MatrixOperation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Checking placement of Tetromino in valid coordinates")
	{
		Tetromino tet = Tetromino(Tetromino::Type::O, Vector2(6, 6));
		REQUIRE(MatrixOperation::canPlaceTetromino(tet.m_coordinates, mat));
	}

	SECTION("Placing Tetromino I at row 6") 
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(1, 6));
		MatrixOperation::placeTetromino(tet.m_coordinates, mat);
		REQUIRE_FALSE(MatrixOperation::rowIsEmpty(mat, 6));
	}

	SECTION("Removing Tetromino I at row 6")
	{
		Tetromino tet = Tetromino(Tetromino::Type::I, Vector2(1, 6));
		MatrixOperation::removeTetromino(tet.m_coordinates, mat);
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 6));
	}
}

TEST_CASE("Dropping floating tiles in a Matrix", "[MatrixOperation, unit]")
{
	SECTION("Dropping two consecutive floating rows")
	{
		Matrix mat;
		MatrixOperation::fillRow(mat, TileState::GROUND, 0);
		MatrixOperation::fillRow(mat, TileState::GROUND, 1);

		CHECK_FALSE(MatrixOperation::rowIsEmpty(mat, 0));
		CHECK_FALSE(MatrixOperation::rowIsEmpty(mat, 1));

		MatrixOperation::dropFloatingRows(mat);

		INFO("Could not drop rows");
		REQUIRE_FALSE(MatrixOperation::rowIsEmpty(mat, MatrixDimensions::HEIGHT - 1));
		REQUIRE_FALSE(MatrixOperation::rowIsEmpty(mat, MatrixDimensions::HEIGHT - 2));

		INFO("Could not clear rows original position")
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 0));
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 1));
	}
}

TEST_CASE("Clearing completed rows", "[MatrixOperation, unit]")
{
	Matrix mat;

	SECTION("Clearing two consecutive rows")
	{
		MatrixOperation::fillRow(mat, TileState::GROUND, 0);
		MatrixOperation::fillRow(mat, TileState::GROUND, 1);

		CHECK_FALSE(MatrixOperation::rowIsEmpty(mat, 0));
		CHECK_FALSE(MatrixOperation::rowIsEmpty(mat, 1));

		MatrixOperation::clearCompletedRows(mat);
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 0));
		REQUIRE(MatrixOperation::rowIsEmpty(mat, 1));
	}
}
