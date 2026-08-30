#include "App.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <chrono>
#include <thread>

void App::loop() {
  // TODO: Consider if this belongs here or in EventHandler
  SDL_Event event;
  while (true) {
    // Record the frame time
    previous_frame_start = current_frame_start;
    current_frame_start = std::chrono::steady_clock::now();
    const auto delta_time = current_frame_start - previous_frame_start;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        return;
      else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        renderer.center_frame_within_window();
    }

    // HACK: Shouldn't this be in EventHandler?
    const auto keyboard = SDL_GetKeyboardState(nullptr);

    // Update game state
    switch (tetris.get_state()) {
      using enum Tetris::State;
    case Running:
      handler.handle_game_events(tetris, keyboard);
      tetris.tick(delta_time);
      handler.tick(tetris, delta_time);
      break;
    case Paused:
      handler.handle_paused_events(tetris, keyboard);
      break;
    case GameOver:
      // TODO: Probably want to check against a different type
      if (handler.handle_game_over_events(tetris, keyboard) == SDL_APP_SUCCESS)
        return;
      break;
    }

    // Render the frame
    renderer.render_frame(tetris);

    // If the frame finished early, sleep
    static constexpr auto expected =
        std::chrono::nanoseconds(1'000'000'000 / 60);
    const auto elapsed = std::chrono::steady_clock::now() - current_frame_start;
    if (elapsed < expected) {
      std::this_thread::sleep_for(expected - elapsed);
    }
  }
}
