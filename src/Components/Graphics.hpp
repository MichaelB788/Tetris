#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include "../Game/Objects/Board.hpp"

typedef struct GraphicsModule
{
    GraphicsModule(SDL_Renderer* ren);

    ~GraphicsModule();

    void setColor(char id);

    void drawBoard(Board board);

    void drawTile(int x, int y, char id);

    void clearAndPresentFrame(Board board);

    private:

    const int tileSize = 40;

    SDL_Renderer* p_renderer;
} GraphicsModule;

#endif
