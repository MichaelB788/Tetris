#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H
#include <cstdint>

/// @brief States which the current tile may take, such as being empty or active
enum class TileState : uint8_t {
  EMPTY = 0,
  ACTIVE,
  GROUNDED,
  GHOST,
};

/// @brief Dimensions of the window
enum Screen {
  WIDTH = 600,
  HEIGHT = 600
};

/// @brief Directions the player can input
enum class Direction : uint8_t {
  NONE,
  RIGHT,
  LEFT,
  DOWN
};

#endif
