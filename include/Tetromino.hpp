#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H
#include "Common.hpp"
#include <cstdint>
#include <span>

class Tetromino {
public:
  static constexpr Point INITIAL_POSITION = {.x = 4, .y = 2};

  explicit Tetromino(TetrominoType type, Point pos = INITIAL_POSITION);

  Tetromino();

  static TetrominoType get_random_type();

  void shift(Point delta);

  void set_position(Point pos);

  void rotate_clockwise();

  void rotate_counterclockwise();

  [[nodiscard]] TetrominoType type() const { return type_; }

  [[nodiscard]] std::span<const Point> view() const {
    return std::span(blocks_);
  }

  [[nodiscard]] std::size_t type_index() const {
    return static_cast<std::size_t>(type_);
  }

  [[nodiscard]] std::size_t prev_rotation() const {
    return static_cast<std::size_t>(rotation_state_.prev);
  }

  [[nodiscard]] std::size_t curr_rotation() const {
    return static_cast<std::size_t>(rotation_state_.curr);
  }

private:
  struct RotationState {
    uint8_t prev, curr;

    void clockwise();

    void counterclockwise();
  };

  TetrominoType type_;

  std::array<Point, 4> blocks_;

  RotationState rotation_state_;
};

#endif
