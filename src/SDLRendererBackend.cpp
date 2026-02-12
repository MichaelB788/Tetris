#include "SDLRendererBackend.hpp"
#include <SDL3/SDL_log.h>

SDLRendererBackend::SDLRendererBackend(SDL_Window *window) {
  renderer_ = SDL_CreateRenderer(window, NULL);
  if (!renderer_) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failure creating SDL_Renderer: %s",
                 SDL_GetError());
    return;
  }
  if (!SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND))
    SDL_LogError(SDL_LOG_CATEGORY_RENDER,
                 "Could not activate SDL Blend mode: %s)", SDL_GetError());
}

SDLRendererBackend::~SDLRendererBackend() {
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
}
