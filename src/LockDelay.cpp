#include "LockDelay.hpp"

void LockDelay::begin_timer_if(bool cond) { lock_pending = cond; }

void LockDelay::perform_lock_reset_if(bool cond) {
  if (cond && lock_pending && lock_resets < lock_reset_limit) {
    ++lock_resets;
    lock_pending = true;
    timer.reset();
  }
}

void LockDelay::reset() {
  lock_pending = false;
  lock_resets = 0;
  lock_reset_limit = 0;
  timer.reset();
}
