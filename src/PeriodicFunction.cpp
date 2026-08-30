#include "PeriodicFunction.hpp"
#include <chrono>
#include <functional>

void PeriodicFunction::invoke_immediately() { std::invoke(function); }

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
