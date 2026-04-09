#pragma once
#include <chrono>

struct Timer {
  std::chrono::nanoseconds duration{0};
  std::chrono::nanoseconds elapsed{0};
};
