#pragma once
#include <chrono>
#include <functional>

// A function which can automatically be called over a period of time.
class PeriodicFunction {
public:
  PeriodicFunction(const PeriodicFunction &) = delete;
  PeriodicFunction(PeriodicFunction &&) = delete;
  PeriodicFunction &operator=(const PeriodicFunction &) = delete;
  PeriodicFunction &operator=(PeriodicFunction &&) = delete;

  template <typename Fn>
  constexpr PeriodicFunction(std::chrono::nanoseconds dur, Fn &&fn)
      : duration(dur), function(fn) {}

  void invoke_immediately();

  void tick(std::chrono::nanoseconds delta);

  void set_duration(std::chrono::nanoseconds dur);

  void reset();

private:
  std::chrono::nanoseconds duration{};
  std::chrono::nanoseconds accumulator{};

  std::function<void()> function;
};
