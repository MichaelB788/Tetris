#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "Playfield.hpp"
#include "GameConstants.hpp"

TEST_CASE("Playfield Constructor and Initialization", "[Playfield][unit]")
{
  SECTION("Default constructor creates correct board size") {
    const Playfield board;

    REQUIRE(board.size() == GameConfig::BOARD_HEIGHT * GameConfig::BOARD_WIDTH);
  }

  SECTION("Tile (0, 10) should be empty")
  {
    const Playfield board;
    auto& tile = board.getTileAt(0, 10);
    auto& before = board.getTileAt(0, 9);
    auto& after = board.getTileAt(0, 11);
    CHECK(before.isEmpty());
    CHECK(after.isEmpty());
    REQUIRE(tile.isEmpty());
  }

  SECTION("All tiles are initially empty") {
    const Playfield board;

    for (int y = 0; y < GameConfig::BOARD_HEIGHT; y++) {
      for (int x = 0; x < GameConfig::BOARD_WIDTH; x++) {
        INFO("Checking tile at position (" << x << ", " << y << ")");
        REQUIRE(board.getTileAt(x, y).isEmpty());
      }
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