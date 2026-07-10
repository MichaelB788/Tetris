#pragma once
#include "EventHandler.hpp"
#include "FPS.hpp"
#include "NumberRenderer.hpp"
#include "PlatformSDL.hpp"
#include "ScreenPos.hpp"
#include "Tetris.hpp"
#include "TextRenderer.hpp"
#include <SDL3/SDL_render.h>
#include <chrono>
#include <random>

struct AppState {
  std::mt19937 rng{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock>
      prev_time = std::chrono::steady_clock::now(),
      curr_time = std::chrono::steady_clock::now();

  FPS fps{60};
  FPS_Counter fps_counter{};

  screen_pos::Playfield pf_pos;
  screen_pos::Text text_pos;

  Tetris tetris{rng};

  EventHandler handler;

  TextRenderer text_renderer{};
  NumberRenderer num_renderer{nullptr, nullptr};

  SDL::Window window = nullptr;
  SDL::Renderer renderer = nullptr;
  SDL::Texture texture_atlas = nullptr;
  SDL::TTF::RendererTextEngine text_engine = nullptr;
  SDL::TTF::Font font = nullptr;
};

void render_frame(AppState &state);
