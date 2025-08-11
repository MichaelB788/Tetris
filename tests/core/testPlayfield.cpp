#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "Playfield.hpp"
#include "GameConstants.hpp"

Playfield populatedPlayfield() 
{
  /**
   * Visual Representation of customBoard
   *
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . . . . . . .
   * . . . . O O O O O O
   * O O O O O O O O O O
   * . . . . O O O O O O
   * O O O O O O O O O O
   * . . . . O O O O O O
   * O O O O O O O O O O
   * . . . . O O O O O O
   * O O O O O O O O O O
   * . . . . O O O O O O
   * O O O O O O O O O O
   * . . . . O O O O O O
   * O O O O O O O O O O
   */
  Playfield customBoard;
  const Tile O = Tile(Type::O, Role::GROUNDED);

  for (int y = 10; y < GameConfig::BOARD_HEIGHT; y++) {
    for (int x = 0; x < GameConfig::BOARD_WIDTH; x++) {
      if (y % 2 == 0) {
        if (x > 4) customBoard.set(x, y, O);
      }
      else {
        customBoard.set(x, y, O);
      }
    }
  }

  return customBoard;
}

TEST_CASE("Playfield Constructor and Initialization", "[Playfield][unit]")
{
  SECTION("Default constructor creates correct board size") {
    const Playfield board;

    REQUIRE(board.size() == GameConfig::BOARD_HEIGHT * GameConfig::BOARD_WIDTH);
  }

  SECTION("Tile (0, 10) should be empty")
  {
    const Playfield board;
    auto& tile = board.at(0, 10);
    auto& before = board.at(0, 9);
    auto& after = board.at(0, 11);
    CHECK(before.isEmpty());
    CHECK(after.isEmpty());
    REQUIRE(tile.isEmpty());
  }

  SECTION("All tiles are initially empty") {
    const Playfield board;

    for (int y = 0; y < GameConfig::BOARD_HEIGHT; y++) {
			INFO("Checking row" << y);
			REQUIRE(board.isRowEmpty(y));
    }
  }

  SECTION("Board dimensions are consistent") {
    const Playfield board;

    // Verify the relationship between size and dimensions
    REQUIRE(board.size() > 0);
    REQUIRE(GameConfig::BOARD_HEIGHT > 0);
    REQUIRE(GameConfig::BOARD_WIDTH > 0);
    REQUIRE(board.size() == static_cast<size_t>(GameConfig::BOARD_HEIGHT * GameConfig::BOARD_WIDTH));
  }
}

TEST_CASE("Board State Management", "[Playfield, unit]")
{
  SECTION("Playfiled clearBoard() function")
  {
    Playfield customBoard = populatedPlayfield();
    CHECK(customBoard.isOccupied(7, 10));

    customBoard.clearBoard();
    for (int y = 0; y < GameConfig::BOARD_HEIGHT; y++) {
      INFO("Checking row " << y);
      REQUIRE(customBoard.isRowEmpty(y));
    }
  }

  SECTION("Playfield isOccupied() function")
  {
    Playfield board;
    board.set(5, 10, Tile(Type::O, Role::GROUNDED));
    REQUIRE(board.isOccupied(5, 10));
    REQUIRE_FALSE(board.isOccupied(0, 0));
  }
}
