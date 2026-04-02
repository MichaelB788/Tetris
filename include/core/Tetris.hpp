#pragma once
#include "core/Matrix.hpp"
#include "core/NextQueue.hpp"
#include "core/Tetromino.hpp"
#include "core/tetris-move.hpp"
#include <cstdint>
#include <optional>
#include <random>

enum class Status : uint8_t { Running, Paused, GameOver };

struct HUD {
  std::optional<Tetromino::Type> held_type = std::nullopt;
  NextQueue next_queue{};
};

struct Board {
  Matrix matrix{};
  Tetromino player{};
};

class Tetris {
public:
  Tetris();

  void move_left() {
    tetris::move::shift_piece(board_.player, board_.matrix, Point::left());
  }

  void move_right() {
    tetris::move::shift_piece(board_.player, board_.matrix, Point::right());
  }

  void move_down() {
    if (!tetris::move::shift_piece(board_.player, board_.matrix,
                                   Point::down())) {
      complete_move();
    }
  }

  void drop();

  void hold();

  void rotate_cw() { tetris::srs::rotate_cw(board_.player, board_.matrix); }

  void rotate_ccw() { tetris::srs::rotate_ccw(board_.player, board_.matrix); }

  [[nodiscard]] const Board &playfield() const { return board_; }

  [[nodiscard]] const HUD &hud() const { return hud_; }

  [[nodiscard]] Status status() const { return status_; }

  [[nodiscard]] int score() const { return score_; }

private:
  bool switch_to_next();

  void complete_move();

  static constexpr Point INIT_POS = {.x = 4, .y = 2};

  std::mt19937 rng_{std::random_device{}()};

  bool hold_command_triggered = false;

  Status status_ = Status::Running;

  int score_ = 0;

  HUD hud_{};

  Board board_{};
};
