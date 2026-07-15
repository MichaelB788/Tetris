#include "LockDelay.hpp"
#include "Tetris.hpp"

void LockDelay::begin_timer_if(bool cond) { lock_pending_ = cond; }

void LockDelay::perform_lock_reset_if(bool cond) {
  if (cond && lock_pending_ && lock_resets_ < lock_reset_limit_) {
    ++lock_resets_;
    timer_.reset();
  }
}

void LockDelay::tick(std::chrono::nanoseconds delta, Tetris &tetris,
                     std::mt19937 &rng) {
  if (lock_pending_) {
    timer_.invoke_when_elapsed(
        delta, [&] { tetris.finalize_move_when_grounded(rng); });
  }
}

void LockDelay::reset() {
  lock_pending_ = false;
  lock_resets_ = 0;
  lock_reset_limit_ = 0;
  timer_.reset();
}
