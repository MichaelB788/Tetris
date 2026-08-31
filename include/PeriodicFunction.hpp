#pragma once
#include <chrono>
#include <functional>

// A function which can automatically invoke itself over a given interval
class PeriodicFunction {
public:
  PeriodicFunction(const PeriodicFunction &) = delete;
  PeriodicFunction(PeriodicFunction &&) = delete;
  PeriodicFunction &operator=(const PeriodicFunction &) = delete;
  PeriodicFunction &operator=(PeriodicFunction &&) = delete;

  template <typename Fn>
  constexpr PeriodicFunction(std::chrono::nanoseconds dur, Fn &&fn)
      : duration(dur), function(fn) {}

  // Invoking early will reset the period
  void invoke_early();

  // Invokes the function once the period has elapsed
  void tick(std::chrono::nanoseconds delta);

  void set_duration(std::chrono::nanoseconds dur);

  void reset();

private:
  std::chrono::nanoseconds duration{};
  std::chrono::nanoseconds accumulator{};

  std::function<void()> function;
};
