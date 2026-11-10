#include "App.hpp"
#include <SDL3/SDL_events.h>
#include <chrono>
#include <thread>

namespace {
constexpr auto TARGET_FPS = std::chrono::nanoseconds(1'000'000'000 / 60);
}

void App::loop() {
  while (true) {
    prev_time = curr_time;
    curr_time = std::chrono::steady_clock::now();
    const auto delta_time = curr_time - prev_time;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        return;
      else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        tetris_renderer.update_layout_on_resize();
    }

    switch (keyboard_listener.process_keystrokes(tetris, delta_time)) {
    case KeyboardListener::AppResult::Continue:
      break;
    case KeyboardListener::AppResult::Quit:
      return;
    }

    switch (tetris.get_state()) {
    case Tetris::State::Running:
      tetris.tick(delta_time);
      break;
    default:
      break;
    }

    tetris_renderer.render_frame(tetris);

    if (const auto elapsed = std::chrono::steady_clock::now() - curr_time;
        elapsed < TARGET_FPS)
      std::this_thread::sleep_for(TARGET_FPS - elapsed);
  }
}
