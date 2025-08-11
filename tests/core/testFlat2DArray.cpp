#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "Flat2DArray.hpp"
#include "GameConstants.hpp"

TEST_CASE("Flat2DArray Construction", "[unit, Flat2DArray]")
{
  SECTION("Default construction")
  {
    Flat2DArray<int, 5, 5> IntegerMatrix;

    REQUIRE(IntegerMatrix.size() == (5 * 5));
    for (int y = 0; y < 5; y++) {
      for (int x = 0; x < 5; x++) {
        INFO("Checking element at position (" << x << ", " << y << ")");
        REQUIRE(IntegerMatrix(x, y) == 0);
      }
    }
  }

  SECTION("Default construction with a 10x22 array")
  {
    const Flat2DArray<int, 10, 22> IntegerMatrix;

    REQUIRE(IntegerMatrix.size() == (10 * 22));

    for (int y = 0; y < 22; y++) {
      for (int x = 0; x < 10; x++) {
        INFO("Checking element at position (" << x << ", " << y << ")");
        REQUIRE(IntegerMatrix(x, y) == 0);
      }
    }
  }

  SECTION("Initializer list construction")
  {
    Flat2DArray<int, 2, 2> IntegerMatrix =
    {
      1, 2,
      3, 4
    };

    REQUIRE(IntegerMatrix.size() == 4);

    int i = 1;
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 2; x++) {
        INFO("Checking element at position (" << x << ", " << y << ")");
        REQUIRE(IntegerMatrix(x, y) == i++);
      }
    }

    Flat2DArray<int, 2, 2> PartiallyFilledMatrix = 
    {
      1, 2,
      3
    };

    REQUIRE(PartiallyFilledMatrix.size() == 4);
    CHECK(PartiallyFilledMatrix(1, 1) == 0);

    Flat2DArray<int, 2, 2> TruncatedMatrix = 
    {
      1, 2,
      3, 4,
      5, 6
    };

    REQUIRE(TruncatedMatrix.size() == 4);
    CHECK_FALSE(TruncatedMatrix(2, 1) == 6);
  }
}

TEST_CASE("Element setters and getters", "[Flat2DArray, unit]")
{
  SECTION("Get an element from a coordinate")
  {
    Flat2DArray<int, 3, 3> IntegerMatrix =
    {
      1, 2, 3,
      4, 5, 6,
      7, 8
    };

    CHECK(IntegerMatrix(2, 2) == 0);
    CHECK(IntegerMatrix(0, 0) == 1);

    Flat2DArray<int, 3, 3> FloatMatrix =
    {
      1, 2, 3,
      4, 5, 6,
      7, 8
    };

    CHECK(IntegerMatrix(2, 2) == 0);
    CHECK(IntegerMatrix(0, 0) == 1);
  }

  SECTION("Set an element from a coordinate")
  {
    Flat2DArray<int, 3, 3> IntegerMatrix =
    {
      1, 2, 3,
      4, 5, 6,
      7, 9
    };

    IntegerMatrix(2, 2) = 9;
    IntegerMatrix(1, 2) = 8;
    CHECK(IntegerMatrix(1, 2) == 8);
    CHECK(IntegerMatrix(2, 2) == 9);
  }
}

TEST_CASE("Const correctness", "[Flat2DArray, unit]")
{
  const Flat2DArray<int, 2, 2> IntegerMatrix =
  {
    1, 2,
    3, 4
  };

  REQUIRE(IntegerMatrix(0, 0) == 1);
}

TEST_CASE("Indexing", "[Flat2DArray, unit]")
{
	SECTION("Integer Matrix Iterator")
	{
    const int rows = 5, cols = 5;
		const Flat2DArray<int, cols, rows> Matrix
    {
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5
    };
    CHECK(Matrix(4, 4) == 5);
    REQUIRE_NOTHROW(Matrix(0, 4));
	}

	SECTION("Cooridnate (5, 5) should throw an exception")
	{
    const int rows = 5, cols = 5;
		const Flat2DArray<int, cols, rows> Matrix
    {
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5,
      1, 2, 3, 4, 5
    };
    REQUIRE_THROWS(Matrix(5, 5));
	}

  SECTION("Tile Matrix Iterator") 
  {
    const int rows = 2, cols = 2;
    Tile O = Tile(Type::O, Role::ACTIVE);
    Flat2DArray<Tile, rows, cols> Matrix =
    {
      O, O,
      O, O
    };

    for (int y = 0; y < rows; y++)
      for (int x = 0; x < cols; x++)
        Matrix(x, y).resetTile();

    bool allIsEmpty = true;
    for (int y = 0; y < rows; y++)
      for (int x = 0; x < cols; x++)
        allIsEmpty = Matrix(x, y).isEmpty();

    REQUIRE(allIsEmpty);
  }
}