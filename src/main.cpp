
#include <iostream>
#include <SDL2/SDL.h>
#include "Components/Window.h"

int main (int argc, char **argv){

    // SDL_Color white = {255, 255, 255};
    SDL_Window *win = NULL;

    Window::init(win);
    Window::open(win);
    Window::close(win);

    return 0;

}
