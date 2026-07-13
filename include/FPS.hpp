#pragma once
#include "Timer.hpp"
#include <chrono>

class FPS {
public:
  explicit FPS(unsigned fps) { set_fps(fps); }

  void set_fps(unsigned val);
  auto get_fps() const -> unsigned;
  auto get_frame_duration() const -> std::chrono::nanoseconds;

private:
  unsigned fps_ = 0;
  std::chrono::nanoseconds frame_duration_ns_{};
};

class FPS_Counter {
public:
  void tick(std::chrono::nanoseconds delta);

  auto get_current_fps() const -> unsigned;

private:
  unsigned ticks_ = 0, current_fps_ = 0;
  Timer<std::chrono::nanoseconds> delay_{std::chrono::seconds(1)};
};
