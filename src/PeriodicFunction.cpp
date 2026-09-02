#include "PeriodicFunction.hpp"
#include <chrono>
#include <functional>

void PeriodicFunction::invoke_early() {
  std::invoke(function);
  period.reset();
}

void PeriodicFunction::tick(std::chrono::nanoseconds delta) {
  period.tick(delta);
  while (period.has_set_off()) {
    period.rewind(period.get_duration());
    std::invoke(function);
  }
}

void PeriodicFunction::set_duration(std::chrono::nanoseconds dur) {
  period.set_duration(dur);
}

void PeriodicFunction::reset() { period.reset(); }
