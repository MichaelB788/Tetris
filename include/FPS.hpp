#pragma once
#include "Timer.hpp"
#include <chrono>

class FPS {
public:
  explicit FPS(unsigned fps) { set_fps(fps); }

  void set_fps(unsigned val);

  auto get_fps() const -> unsigned { return fps_; }

  auto get_frame_duration() const -> std::chrono::nanoseconds {
    return frame_duration_ns_;
  }

private:
  unsigned fps_ = 0;
  std::chrono::nanoseconds frame_duration_ns_{};
};

class FPS_Counter {
public:
  void tick(std::chrono::nanoseconds delta);

  auto get_current_fps() const -> unsigned { return current_fps_; }

private:
  unsigned ticks_ = 0, current_fps_ = 0;
  Timer delay_{std::chrono::seconds(1)};
};
