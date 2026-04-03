#pragma once
#include "Matrix.hpp"
#include "NextQueue.hpp"
#include "Tetromino.hpp"
#include <optional>

enum class Status : uint8_t { Running, Paused, GameOver };

struct HUD {
  std::optional<Tetromino::Type> held_type = std::nullopt;
  NextQueue next_queue{};
};

struct Board {
  Matrix matrix{};
  Tetromino player{};
};
