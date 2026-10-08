#include "Tetris.hpp"
#include "Piece.hpp"
#include "Point.hpp"
#include <algorithm>
#include <chrono>
#include <optional>
#include <random>

Tetris::Tetris(std::mt19937 &rng_)
    : rng(rng_),
      gravity_func(std::chrono::seconds(1), [this] { player_soft_drop(); }),
      lock_reset{.func{std::chrono::seconds(1), [this] {
                         if (!matrix.can_place(piece::create_shape(
                                 piece::shift(player, {.y = 1})))) {
                           lock_piece();
                           state = start_next_round(
                               tetris::seven_bag::pop(bag, rng));
                         }
                       }}} {
  tetris::seven_bag::shuffle(bag, rng);
  player = tetris::create_next_piece(tetris::seven_bag::pop(bag, rng));
}

void Tetris::player_step_left() { player_horizontal_shift(-1); }

void Tetris::player_step_right() { player_horizontal_shift(1); }

void Tetris::player_soft_drop() {
  if (const auto shifted = piece::shift_within(player, {.y = 1}, matrix))
    player = shifted.value();
  else
    lock_reset.countdown_enabled = true;
}

void Tetris::player_hard_drop() {
  player = piece::hard_drop(player, matrix);
  lock_piece();
  state = start_next_round(tetris::seven_bag::pop(bag, rng));
}

void Tetris::player_rotate_cw() { player_rotate(Piece::Rotation::Clockwise); }

void Tetris::player_rotate_ccw() {
  player_rotate(Piece::Rotation::Counterclockwise);
}

void Tetris::player_rotate_half() { player_rotate(Piece::Rotation::Half); }

void Tetris::hold_current_piece() {
  if (!held_piece.action_used) {
    const auto temp = player.type;
    state =
        start_next_round(held_piece.type ? held_piece.type.value()
                                         : tetris::seven_bag::pop(bag, rng));
    held_piece.type = temp;
    held_piece.action_used = true;
  }
}

void Tetris::pause_game() {
  if (state == State::Running)
    state = State::Paused;
}

void Tetris::unpause_game() {
  if (state == State::Paused)
    state = State::Running;
}

void Tetris::tick(std::chrono::nanoseconds delta_time) {
  gravity_func.tick(delta_time);

  if (lock_reset.countdown_enabled)
    lock_reset.func.tick(delta_time);
}

void Tetris::reset() {
  state = State::Running;
  score = lock_reset.count = 0;
  held_piece.action_used = lock_reset.countdown_enabled = false;

  gravity_func.reset();
  lock_reset.func.reset();

  held_piece.type = std::nullopt;
  matrix.clear();
  tetris::seven_bag::shuffle(bag, rng);
  player = tetris::create_next_piece(tetris::seven_bag::pop(bag, rng));
}

void Tetris::player_horizontal_shift(float x) {
  if (const auto shifted = piece::shift_within(player, {.x = x}, matrix)) {
    player = shifted.value();
    tetris::lock_reset::attempt_reset(lock_reset);
  }
}

void Tetris::player_rotate(Piece::Rotation next) {
  if (const auto rotated = piece::rotate_srs(player, next, matrix)) {
    player = rotated.value();
    tetris::lock_reset::attempt_reset(lock_reset);
  }
}

auto Tetris::start_next_round(Piece::Type next) -> State {
  player = tetris::create_next_piece(next);

  // Try to adjust the initial position of the next piece
  while (!matrix.can_place(piece::create_shape(player))) {
    --player.pos.y;
    if (!matrix::is_piece_within_bounds(piece::create_shape(player)))
      return State::GameOver;
  }

  // Adjustment successful, reset round specific variables for next round
  lock_reset.func.reset();
  gravity_func.reset();
  lock_reset.count = 0;
  lock_reset.countdown_enabled = false;

  return State::Running;
}

void Tetris::lock_piece() {
  held_piece.action_used = false;
  matrix.lock_down(player);
  score += matrix.clear_lines();

  using namespace std::chrono_literals;
  static constexpr std::array LEVELS{1000ms, 900ms, 800ms, 700ms, 600ms, 500ms,
                                     450ms,  400ms, 300ms, 200ms, 100ms};
  gravity_func.set_duration(score < 100 ? LEVELS[score / 10]
                                        : std::chrono::milliseconds(100));
}

auto tetris::create_next_piece(Piece::Type type) -> Piece {
  return {type, {4, 4}};
}

void tetris::lock_reset::attempt_reset(Tetris::LockReset &lock_reset) {
  if (lock_reset.countdown_enabled && lock_reset.count < 10) {
    ++lock_reset.count;
    lock_reset.func.reset();
  }
}

void tetris::seven_bag::shuffle(Tetris::SevenBag &bag, std::mt19937 &rng) {
  bag.read_idx = 0;
  bag.current = bag.next;
  std::shuffle(bag.next.begin(), bag.next.end(), rng);

  if (bag.current.back() == bag.next.front())
    std::swap(bag.next.front(), bag.next[3]);
}

auto tetris::seven_bag::pop(Tetris::SevenBag &bag, std::mt19937 &rng)
    -> Piece::Type {
  const auto next = bag.current[bag.read_idx++];
  if (bag.read_idx == 7)
    tetris::seven_bag::shuffle(bag, rng);
  return next;
}

auto tetris::seven_bag::create_preview(const Tetris::SevenBag &bag)
    -> Tetris::SevenBag::Preview {
  Tetris::SevenBag::Preview preview{};
  for (size_t i = 0; i < preview.size(); ++i) {
    const auto idx = bag.read_idx + i;
    preview[i] = idx < 7 ? bag.current[idx] : bag.next[idx - 7];
  }
  return preview;
}

auto Tetris::get_state() const -> State { return state; }
auto Tetris::get_score() const -> unsigned { return score; }
auto Tetris::get_matrix() const -> const Matrix & { return matrix; }
auto Tetris::get_active_piece() const -> Piece { return player; }
auto Tetris::get_seven_bag_preview() const -> SevenBag::Preview {
  return tetris::seven_bag::create_preview(bag);
}
auto Tetris::get_held_piece_type() const -> std::optional<Piece::Type> {
  return held_piece.type;
}
auto Tetris::get_ghost_piece() const -> Piece {
  return piece::hard_drop(player, matrix);
}
