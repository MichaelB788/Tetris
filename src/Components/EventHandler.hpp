#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

namespace EventHandler 
{
    void process(SDL_Event event, bool gameState);

    void keydown(SDL_Event event);
    void keyup(SDL_Event event);
}

#endif
