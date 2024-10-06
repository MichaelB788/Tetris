#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

namespace EventHandler 
{
    void handle(SDL_Event &event);

    void quit();
    void keydown(SDL_Event);
    void keyup(SDL_Event);
}

#endif
