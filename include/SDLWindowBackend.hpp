#ifndef SDL_WINDOW_BACKEND_HPP
#define SDL_WINDOW_BACKEND_HPP
#include "IWindow.hpp"
#include <SDL3/SDL_video.h>

class SDLWindowBackend : public IWindow {
public:
  SDLWindowBackend(const char *title, SDL_WindowFlags flags,
                   WinSize size = {600, 600});

  [[nodiscard]] bool initialized() const override { return window_ != nullptr; }

  [[nodiscard]] SDL_Window *sdl_window() { return window_; }

  void cache_window_size() override {
    SDL_GetWindowSizeInPixels(window_, &size_.w, &size_.h);
  }

  WinSize get_window_size() const override { return size_; }

  ~SDLWindowBackend() override;

private:
  SDL_Window *window_ = nullptr;

  WinSize size_;
};

#endif
