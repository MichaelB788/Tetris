#include "SDLWindowBackend.hpp"
#include <SDL3/SDL_log.h>

SDLWindowBackend::SDLWindowBackend(const char *title, SDL_WindowFlags flags,
                                   WinSize size)
    : size_(size) {
  window_ = SDL_CreateWindow(title, size_.w, size_.h, flags);
  if (!window_)
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failure creating SDL_Window: %s",
                 SDL_GetError());
}

SDLWindowBackend::~SDLWindowBackend() {
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
}
