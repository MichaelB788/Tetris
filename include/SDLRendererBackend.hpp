#ifndef SDL_RENDERER_BACKEND_HPP
#define SDL_RENDERER_BACKEND_HPP
#include "IRenderer.hpp"
#include <SDL3/SDL_render.h>

class SDLRendererBackend : public IRenderer {
public:
  SDLRendererBackend(SDL_Window *window);

  [[nodiscard]] bool initialized() const override {
    return renderer_ != nullptr;
  }

  void clear() override { SDL_RenderClear(renderer_); }

  void present() override { SDL_RenderPresent(renderer_); }

  void set_color(Color color) override {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  }

  void render_rects(std::span<RectF> rects) override {
    SDL_RenderRects(renderer_,
                    reinterpret_cast<const SDL_FRect *>(rects.data()),
                    static_cast<int>(rects.size()));
  }

  void render_fill_rects(std::span<RectF> rects) override {
    SDL_RenderFillRects(renderer_,
                        reinterpret_cast<const SDL_FRect *>(rects.data()),
                        static_cast<int>(rects.size()));
  }

  ~SDLRendererBackend() override;

private:
  SDL_Renderer *renderer_ = nullptr;
};

#endif
