#include <FPS.hpp>

void FPS::set_fps(unsigned val) {
  fps_ = val;
  frame_duration_ns_ = std::chrono::nanoseconds{1'000'000'000 / fps_};
}

void FPS_Counter::tick(std::chrono::nanoseconds delta) {
  ++ticks_;
  delay_.invoke_periodically(delta, [this] {
    current_fps_ = ticks_;
    ticks_ = 0;
  });
}
