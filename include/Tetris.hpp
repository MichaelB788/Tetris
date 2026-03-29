#pragma once
#include "NextQueue.hpp"
#include "Playfield.hpp"
#include "Point.hpp"
#include <cstdint>
#include <optional>

enum class Status : uint8_t { Running, Paused, GameOver };

struct HeldTetromino {
  std::optional<Tetromino::Type> held;
  bool held_for_round = false;
};

class Tetris {
public:
  Tetris() : playfield_(queue_.pop()) {}

  void move_left() { playfield_.shift_player({-1, 0}); }

  void move_right() { playfield_.shift_player({1, 0}); }

  void move_down() {
    if (playfield_.can_shift_player({0, 1})) {
      playfield_.shift_player({0, 1});
    } else {
      playfield_.lock_piece();
      // switch to next
    }
  }

  void drop() { playfield_.set_player_piece(playfield_.compute_drop()); }

  void hold();

  void rotate_clockwise() { playfield_.rotate_piece_cw(); }

  void rotate_counterclockwise() { playfield_.rotate_piece_ccw(); }

  void reset();

public:
  [[nodiscard]] const Tetromino &current() const { return player_; }

  [[nodiscard]] const Matrix &matrix() const { return matrix_; }

  [[nodiscard]] const Tetromino &optional_hold() const { return hold_; }

  [[nodiscard]] const NextQueue &next_queue() const { return queue_; }

  [[nodiscard]] int score() const { return cleared_; }

private:
  bool shift_current(Point delta);

private:
  void lock_piece();

  void spawn_next();

private:
  HeldTetromino held_{};

  NextQueue queue_{};

  Playfield playfield_;

  Status status_{};

  unsigned cleared_ = 0;
};
