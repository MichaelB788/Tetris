#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

/*
 * A structure which handles game rendering given an SDL Renderer.
 *
 * This structure paints squares based on a set tilesize, 40 pixels.
 * It's primary objective is to clear the screen, and then draw a
 * 10x20 grid.
 **/
typedef struct GraphicsModule
{
    GraphicsModule(SDL_Renderer* ren);

    ~GraphicsModule();

    void setColor(char id);

    void drawBoard();

    void drawTile(int x, int y, char id);

    void clearAndPresentFrame();

    private:

    unsigned int const tileSize = 40;

    SDL_Renderer* p_renderer;
} GraphicsModule;

#endif
