#pragma once
#include "core/NextQueue.hpp"
#include "core/Playfield.hpp"
#include <cstdint>
#include <optional>
#include <random>

enum class Status : uint8_t { Running, Paused, GameOver };

class Tetris {
public:
  Tetris();

  void move_left() { playfield_.shift_player(Point::left()); }

  void move_right() { playfield_.shift_player(Point::right()); }

  void move_down() {
    if (!playfield_.shift_player(Point::down())) {
      complete_move();
    }
  }

  void drop();

  void hold();

  void rotate_clockwise() { playfield_.rotate_player_cw(); }

  void rotate_counterclockwise() { playfield_.rotate_player_ccw(); }

  void reset();

  [[nodiscard]] const Playfield &playfield() const { return playfield_; }

  [[nodiscard]] const std::optional<Tetromino::Type> &held() const {
    return held_;
  }

  [[nodiscard]] const NextQueue &next_queue() const { return next_queue_; }

  [[nodiscard]] Status status() const { return status_; }

  [[nodiscard]] int score() const { return score_; }

private:
  void complete_move();

  std::mt19937 rng_;

  std::optional<Tetromino::Type> held_ = std::nullopt;

  bool hold_command_triggered = false;

  NextQueue next_queue_{};

  Playfield playfield_{};

  Status status_{};

  int score_ = 0;
};
