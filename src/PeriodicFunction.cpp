#include "PeriodicFunction.hpp"
#include <chrono>
#include <functional>

void PeriodicFunction::invoke_early() {
  std::invoke(function);
  accumulator = std::chrono::nanoseconds::zero();
}

void PeriodicFunction::tick(std::chrono::nanoseconds delta) {
  accumulator += delta;
  while (accumulator >= duration) {
    accumulator -= duration;
    std::invoke(function);
  }
}

void PeriodicFunction::set_duration(std::chrono::nanoseconds dur) {
  duration = dur;
}

void PeriodicFunction::reset() {
  accumulator = std::chrono::nanoseconds::zero();
}
