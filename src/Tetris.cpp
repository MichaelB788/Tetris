#include "Tetris.hpp"
#include "Point.hpp"
#include "Tetromino.hpp"
#include <chrono>
#include <optional>

void Tetris::move_left() { move_active({.x = -1}); }

void Tetris::move_right() { move_active({.x = 1}); }

void Tetris::soft_drop() { lock_delay.begin_timer_if(!move_active({.y = 1})); }

void Tetris::hard_drop() {
  active_piece.hard_drop(matrix);
  finalize_move();
}

void Tetris::rotate_cw() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 1));
}

void Tetris::rotate_ccw() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 3));
}

void Tetris::rotate_half() {
  rotate_active(tetromino::rotated_cw(active_piece.get_rotation(), 2));
}

void Tetris::hold_active() {
  if (hold_command_triggered) {
    return;
  }

  const auto to_hold = active_piece.get_type();
  if (try_spawn_next(held_piece.has_value() ? held_piece.value()
                                            : seven_bag.pop())) {
    hold_command_triggered = true;
    held_piece = to_hold;
  } else {
    state = State::GameOver;
  }
}

void Tetris::pause() {
  if (state == State::Running) {
    state = State::Paused;
  }
}

void Tetris::unpause() {
  if (state == State::Paused) {
    state = State::Running;
  }
}

void Tetris::tick(std::chrono::nanoseconds delta_time) {
  gravity_delay.invoke_periodically(delta_time, [this] {
    lock_delay.begin_timer_if(!active_piece.try_shift({.y = 1}, matrix));
  });

  lock_delay.tick(delta_time, [this] {
    if (!matrix.is_move_valid(active_piece.get_shifted_shape({.y = 1}))) {
      finalize_move();
    }
  });
}

void Tetris::reset() {
  state = State::Running;
  score = 0;
  hold_command_triggered = false;

  gravity_delay.reset();
  lock_delay.reset();

  held_piece = std::nullopt;
  matrix.clear();
  seven_bag.shuffle();
  active_piece = {seven_bag.pop(), SPAWN_POINT};
}

auto Tetris::get_state() const -> State { return state; }

auto Tetris::get_score() const -> unsigned { return score; }

auto Tetris::get_matrix() const -> const Matrix & { return matrix; }

auto Tetris::get_active_piece() const -> Tetromino { return active_piece; }

auto Tetris::get_seven_bag() const -> SevenBag::Preview {
  return seven_bag.get_preview();
}

auto Tetris::get_held_piece() const -> std::optional<Tetromino::Type> {
  return held_piece;
}

auto Tetris::get_ghost_piece() const -> Tetromino {
  return {active_piece.get_type(), active_piece.get_pos_after_hard_drop(matrix),
          active_piece.get_rotation()};
}

auto Tetris::move_active(Point<int> delta) -> bool {
  const auto has_shifted = active_piece.try_shift(delta, matrix);
  lock_delay.perform_lock_reset_if(has_shifted);
  return has_shifted;
}

auto Tetris::rotate_active(Tetromino::Rotation next) -> bool {
  const auto has_rotated = active_piece.srs_rotation(next, matrix);
  lock_delay.perform_lock_reset_if(has_rotated);
  return has_rotated;
}

auto Tetris::try_spawn_next(Tetromino::Type next) -> bool {
  active_piece = {next, SPAWN_POINT};

  auto was_successful_turn = true;
  while (matrix.is_shape_hitting_ground(active_piece.get_shape())) {
    active_piece.shift({.y = -1});
    was_successful_turn = matrix.is_move_valid(active_piece.get_shape());
  }

  if (was_successful_turn) {
    lock_delay.reset();
    gravity_delay.reset();
  }

  return was_successful_turn;
}

void Tetris::update_level() {
  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};

  gravity_delay.set_duration(score < 100 ? LEVELS[score / 10] : LEVELS.back());
}

void Tetris::finalize_move() {
  matrix.lock_down(active_piece);
  score += matrix.clear_lines();

  update_level();

  if (try_spawn_next(seven_bag.pop())) {
    hold_command_triggered = false;
  } else {
    state = State::GameOver;
  }
}
