#include <SDL2/SDL.h>
#include <iostream>

#include "EventHandler.hpp"

void EventHandler::handle(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            break;
        case SDL_KEYDOWN:
            break;
        case SDL_KEYUP:
            break;
        default:
            std::cout << "No event detected" << std::endl;
            break;
    }
}

void EventHandler::quit();

void EventHandler::keydown(SDL_Event);

void EventHandler::keyup(SDL_Event);
