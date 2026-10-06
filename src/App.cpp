#include "App.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <thread>

void App::loop() {
  while (true) {
    // Record the frame time
    prev_time = curr_time;
    curr_time = std::chrono::steady_clock::now();
    const auto delta_time = curr_time - prev_time;

    // Poll events
    // NOTE: It is imperitive that this happens before keyboard input is
    // processed
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        return;
      else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        renderer.fit_context_within_window();
    }

    // Handle keyboard input
    switch (keyboard_listener.process_input(delta_time)) {
    case KeyboardListener::AppResult::Continue:
      break;
    case KeyboardListener::AppResult::Quit:
      return;
    }

    // Update game state
    if (tetris.get_state() == Tetris::State::Running)
      tetris.tick(delta_time);

    // Render the frame
    renderer.render_frame(tetris);

    // If the frame finished early, sleep
    static constexpr auto expected =
        std::chrono::nanoseconds(1'000'000'000 / 60);
    const auto elapsed = std::chrono::steady_clock::now() - curr_time;
    if (elapsed < expected) {
      std::this_thread::sleep_for(expected - elapsed);
    }
  }
}
