#include <catch2/catch.hpp>
#include "core/matrix.hpp"
#include "core/matrix-operations.hpp"

TEST_CASE("Flat2DArray Construction", "[unit, Flat2DArray]")
{
  SECTION("Default construction")
  {
    Flat2DArray<int, 3, 2> IntegerMatrix;

    REQUIRE(IntegerMatrix.size() == 6);
    CHECK(IntegerMatrix(0, 0) == 0);
  }

  SECTION("Initializer list construction")
  {
    Flat2DArray<int, 2, 2> IntegerMatrix =
    {
      1, 2,
      3, 4
    };

    REQUIRE(IntegerMatrix.size() == 4);
		CHECK(IntegerMatrix(0, 0) == 1);
		CHECK(IntegerMatrix(1, 0) == 2);
		CHECK(IntegerMatrix(0, 1) == 3);
		CHECK(IntegerMatrix(1, 1) == 4);

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

TEST_CASE("Iterator", "[Flat2DArray, unit]")
{
	SECTION("Integer Matrix Iterator")
	{
		Flat2DArray<int, 2, 2> Matrix{ 1, 2, 3, 4 };
		int sum = 0;
		for (const auto& v : Matrix) sum += v;
		CHECK(sum == 10);
	}

  SECTION("TileState Matrix Iterator") 
  {
    TileState O = TileState(TileType::O, TileRole::ACTIVE);
    Flat2DArray<TileState, 2, 2> Matrix =
    {
      O, O,
      O, O
    };

    for (auto& tile : Matrix) tile.resetTile();
    CHECK(Matrix(1, 1).isEmpty());
  }
}