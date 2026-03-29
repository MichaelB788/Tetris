#pragma once
#include "Point.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

static constexpr size_t NUM_TETROMINOS = 7;

static constexpr size_t NUM_ROTATIONS = 4;

class Tetromino {
public:
  using Shape = std::array<Point, 4>;

  enum Type : uint8_t { I = 0, O, T, S, Z, J, L };

  enum Rotation : uint8_t { R0 = 0, R90, R180, R270 };

  constexpr Tetromino(Type t = I, Point pos = {0, 0})
      : type_(t), pos_(pos), rotation_(R0) {}

  static Type random_type();

  static Tetromino random_piece();

  void shift(Point delta) { pos_ += delta; }

  void set_pos(Point pos) { pos_ = pos; }

  void rotate_cw() {
    rotation_ = static_cast<Rotation>((rotation_ + 1) % NUM_ROTATIONS);
  }

  void rotate_ccw() {
    rotation_ =
        static_cast<Rotation>((rotation_ + NUM_ROTATIONS - 1) % NUM_ROTATIONS);
  }

  [[nodiscard]] Rotation rotation() const { return rotation_; }

  [[nodiscard]] Shape shape() const;

  [[nodiscard]] Type type() const { return type_; }

  [[nodiscard]] Point pos() const { return pos_; }

private:
  Type type_;

  Point pos_;

  Rotation rotation_;

private:
  static constexpr Point SHAPES[NUM_TETROMINOS][NUM_ROTATIONS][4]{
      // I
      {{{-2, 0}, {-1, 0}, {0, 0}, {1, 0}},  // R0
       {{0, -2}, {0, -1}, {0, 0}, {0, 1}},  // R90
       {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}},  // R180
       {{0, -2}, {0, -1}, {0, 0}, {0, 1}}}, // R270

      // O
      {{{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R0
       {{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R90
       {{0, 0}, {1, 0}, {0, -1}, {1, -1}},  // R180
       {{0, 0}, {1, 0}, {0, -1}, {1, -1}}}, // R270

      // T
      {{{-1, 0}, {0, 0}, {1, 0}, {0, -1}},  // R0
       {{0, 1}, {0, 0}, {0, -1}, {1, 0}},   // R90
       {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},   // R180
       {{0, 1}, {0, 0}, {0, -1}, {-1, 0}}}, // R270

      // S
      {{{0, 0}, {1, 0}, {-1, -1}, {0, -1}}, // R0
       {{0, 0}, {0, -1}, {1, 0}, {1, 1}},   // R90
       {{0, 0}, {1, 0}, {-1, -1}, {0, -1}}, // R180
       {{0, 0}, {0, -1}, {1, 0}, {1, 1}}},  // R270

      // Z
      {{{-1, 0}, {0, 0}, {0, -1}, {1, -1}}, // R0
       {{0, -1}, {0, 0}, {1, 0}, {1, 1}},   // R90
       {{-1, 0}, {0, 0}, {0, -1}, {1, -1}}, // R180
       {{0, -1}, {0, 0}, {1, 0}, {1, 1}}},  // R270

      // J
      {{{-1, 0}, {0, 0}, {1, 0}, {-1, -1}}, // R0
       {{0, 1}, {0, 0}, {0, -1}, {1, -1}},  // R90
       {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},   // R180
       {{0, 1}, {0, 0}, {0, -1}, {-1, 1}}}, // R270

      // L
      {{{-1, 0}, {0, 0}, {1, 0}, {1, -1}},   // R0
       {{0, -1}, {0, 0}, {0, 1}, {1, 1}},    // R90
       {{-1, 0}, {0, 0}, {1, 0}, {-1, 1}},   // R180
       {{0, -1}, {0, 0}, {0, 1}, {-1, -1}}}, // R270
  };
};
