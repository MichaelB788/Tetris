#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "util/vector2.hpp"
#include "core/matrix.hpp"
#include "core/matrix-operations.hpp"

TEST_CASE("Matrix initialization", "[Matrix, Vector2, unit]")
{
  Matrix matrix;

  SECTION("Matrix construction")
  {
    for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++)
    {
      if (x == 0 || x == MatrixDimensions::WIDTH - 1)
      {
        INFO("Position recorded at (" << x << ", " << 0 << ")");
        REQUIRE(matrix(x, 0) == TileState::WALL);
      }
      else
      {
        INFO("Position recorded at (" << x << ", " << 0 << ")");
        REQUIRE(matrix(x, 0) == TileState::EMPTY);
      }
    }

    for (unsigned int x = 0; x < MatrixDimensions::WIDTH; x++)
    {
      if (x == 0 || x == MatrixDimensions::WIDTH - 1)
      {
        INFO("Position recorded at (" << x << ", " << MatrixDimensions::HEIGHT - 1 << ")");
        REQUIRE(matrix(x, MatrixDimensions::HEIGHT - 1) == TileState::WALL);
      }
      else
      {
        INFO("Position recorded at (" << x << ", " << MatrixDimensions::HEIGHT - 1 << ")");
        REQUIRE(matrix(x, MatrixDimensions::HEIGHT - 1) == TileState::GROUND);
      }
    }
  }
}

TEST_CASE("Matrix Operations", "[Matrix, Vector2, unit]")
{
  Matrix matrix;

  SECTION("Clear Matrix function") {
    for (int i = 0; i < MatrixDimensions::WIDTH; i++) {
      matrix(i, 0) = TileState::ACTIVE;
      REQUIRE(matrix(i, 0) == TileState::ACTIVE);
    }

    MatrixOperation::clear(matrix);
    for (int i = 0; i < MatrixDimensions::WIDTH; i++) {
      if (i == 0 || i == MatrixDimensions::WIDTH - 1) {
        REQUIRE(matrix(i, 0) == TileState::WALL);
      } else {
        REQUIRE(matrix(i, 0) == TileState::EMPTY);
      }
    }
  }
}