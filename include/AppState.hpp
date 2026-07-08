#pragma once
#include "EventHandler.hpp"
#include "FPS.hpp"
#include "GameRenderer.hpp"
#include "NumberRenderer.hpp"
#include "PlatformSDL.hpp"
#include "Tetris.hpp"
#include "TextRenderer.hpp"
#include <SDL3/SDL_render.h>
#include <chrono>
#include <random>

struct AppState {
  std::mt19937 rng_{std::random_device{}()};

  std::chrono::time_point<std::chrono::steady_clock> prev_time =
      std::chrono::steady_clock::now();
  std::chrono::time_point<std::chrono::steady_clock> curr_time =
      std::chrono::steady_clock::now();
  FPS fps = 60;
  FPS_Counter fps_counter_{};

  Tetris tetris_{rng_};

  // GameRenderer game_renderer_;

  EventHandler handler_;
  TextRenderer text_renderer{};
  NumberRenderer num_renderer{};

  SDL::Window window = nullptr;
  SDL::Renderer renderer = nullptr;
  SDL::Texture piece_atlas = nullptr;
  SDL::TTF::RendererTextEngine text_engine = nullptr;
  SDL::TTF::Font font = nullptr;
};
