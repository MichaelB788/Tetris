#include <FPS.hpp>

void FPS::set_fps(unsigned val) {
  fps_ = val;
  frame_duration_ns_ = std::chrono::nanoseconds{1'000'000'000 / fps_};
}

auto FPS::get_fps() const -> unsigned { return fps_; }

auto FPS::get_frame_duration() const -> std::chrono::nanoseconds {
  return frame_duration_ns_;
}

void FPS_Counter::tick(std::chrono::nanoseconds delta) {
  ++ticks_;
  delay_.invoke_periodically(delta, [this] {
    current_fps_ = ticks_;
    ticks_ = 0;
  });
}

auto FPS_Counter::get_current_fps() const -> unsigned { return current_fps_; }
