#include "LockDelay.hpp"

void LockDelay::begin_timer_if(bool cond) { lock_pending_ = cond; }

void LockDelay::perform_lock_reset_if(bool cond) {
  if (cond && lock_pending_ && lock_resets_ < lock_reset_limit_) {
    ++lock_resets_;
    lock_pending_ = true;
    timer_.reset();
  }
}

void LockDelay::reset() {
  lock_pending_ = false;
  lock_resets_ = 0;
  lock_reset_limit_ = 0;
  timer_.reset();
}
