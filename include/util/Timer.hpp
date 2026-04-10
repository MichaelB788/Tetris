#pragma once
#include <chrono>

class Timer {
public:
  Timer(std::chrono::nanoseconds duration) : duration_(duration) {}

  void operator+=(std::chrono::nanoseconds delta) { elapsed_ += delta; }

  template <typename Fn>
  void tick(std::chrono::nanoseconds delta, Fn &&do_action);

  void set_duration(std::chrono::nanoseconds duration) { duration_ = duration; }

  void reset() { elapsed_ = {}; }

  [[nodiscard]] auto has_set_off() const -> bool {
    return elapsed_ >= duration_;
  }

  [[nodiscard]] auto duration() const -> std::chrono::nanoseconds {
    return duration_;
  }

  [[nodiscard]] auto elapsed() const -> std::chrono::nanoseconds {
    return elapsed_;
  }

private:
  std::chrono::nanoseconds duration_{0};

  std::chrono::nanoseconds elapsed_{0};
};

template <typename Fn>
inline void Timer::tick(std::chrono::nanoseconds delta, Fn &&function) {
  if (has_set_off()) {
    function();
    elapsed_ = {};
  } else {
    elapsed_ += delta;
  }
}
