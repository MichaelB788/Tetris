#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

typedef struct GraphicsModule
{
    GraphicsModule(SDL_Renderer* ren);

    ~GraphicsModule();

    void setColor(char id);

    void drawBoard();

    void drawTile(int x, int y, char id);

    void clearAndPresentFrame();

    private:

    const int tileSize = 40;

    SDL_Renderer* p_renderer;
} GraphicsModule;

#endif
