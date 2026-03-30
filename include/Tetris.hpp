#pragma once
#include "NextQueue.hpp"
#include "Playfield.hpp"
#include <cstdint>
#include <optional>

enum class Status : uint8_t { Running, Paused, GameOver };

struct HeldTetromino {
  std::optional<Tetromino::Type> type;
  bool command_triggered = false;
};

class Tetris {
public:
  Tetris() { playfield_.set_player_unchecked(next_queue_.pop()); }

  void move_left() { playfield_.shift_player({-1, 0}); }

  void move_right() { playfield_.shift_player({1, 0}); }

  void move_down() {
    if (!playfield_.shift_player({0, 1})) {
      complete_move();
    }
  }

  void drop() {
    playfield_.shift_player(playfield_.compute_drop_distance());
    complete_move();
  }

  void hold();

  void rotate_clockwise() { playfield_.rotate_player_cw(); }

  void rotate_counterclockwise() { playfield_.rotate_player_ccw(); }

  void reset();

public:
  [[nodiscard]] const Playfield &playfield() const { return playfield_; }

  [[nodiscard]] const HeldTetromino &held() const { return held_; }

  [[nodiscard]] const NextQueue &next_queue() const { return next_queue_; }

  [[nodiscard]] Status status() const { return status_; }

  [[nodiscard]] int score() const { return score_; }

private:
  void complete_move();

private:
  HeldTetromino held_{};

  NextQueue next_queue_{};

  Playfield playfield_{};

  Status status_{};

  int score_ = 0;
};
