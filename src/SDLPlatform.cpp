#include "SDLPlatform.hpp"
#include "SDLRendererBackend.hpp"
#include "SDLWindowBackend.hpp"
#include <SDL3/SDL_log.h>

SDLPlatform::SDLPlatform() {
  if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Could not initialize SDL subsystems: %s", SDL_GetError());
}

Backends SDLPlatform::create_backends() {
  auto window =
      std::make_unique<SDLWindowBackend>("Tetris", SDL_WINDOW_RESIZABLE);
  auto renderer = std::make_unique<SDLRendererBackend>(window->sdl_window());
  return {std::move(window), std::move(renderer)};
}
