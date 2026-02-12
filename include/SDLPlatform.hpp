#ifndef SDL_PLATFORM_HPP
#define SDL_PLATFORM_HPP
#include "IPlatform.hpp"
#include <SDL3/SDL_init.h>

class SDLPlatform : public IPlatform {
public:
  SDLPlatform();

  ~SDLPlatform() override { SDL_Quit(); }

  Backends create_backends() override;
};

#endif
