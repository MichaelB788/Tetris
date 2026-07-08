#pragma once
#include <chrono>

class Timer {
public:
  explicit Timer(std::chrono::nanoseconds duration) : duration_(duration) {}

  void operator+=(std::chrono::nanoseconds delta) { accumulator_ += delta; }

  template <typename Fn>
  void invoke_when_elapsed(Fn &&function, std::chrono::nanoseconds delta);

  template <typename Fn>
  void invoke_periodically(Fn &&function, std::chrono::nanoseconds delta);

  void set_duration(std::chrono::nanoseconds duration) { duration_ = duration; }

  void reset() { accumulator_ = {}; }

  [[nodiscard]] auto has_elapsed() const -> bool {
    return accumulator_ >= duration_;
  }

  [[nodiscard]] auto duration() const -> std::chrono::nanoseconds {
    return duration_;
  }

  [[nodiscard]] auto accumulator() const -> std::chrono::nanoseconds {
    return accumulator_;
  }

private:
  std::chrono::nanoseconds duration_{0};

  std::chrono::nanoseconds accumulator_{0};
};

template <typename Fn>
void Timer::invoke_when_elapsed(Fn &&function,
                                       std::chrono::nanoseconds delta) {
  accumulator_ += delta;
  if (has_elapsed()) {
    function();
  }
}

template <typename Fn>
void Timer::invoke_periodically(Fn &&function,
                                       std::chrono::nanoseconds delta) {
  accumulator_ += delta;
  while (has_elapsed()) {
    accumulator_ -= duration_;
    function();
  }
}
