#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "Objects/TetrisBoard.hpp"

void Tetris::runGame(GraphicsModule graphics)
{
    EventHandler handler = EventHandler(&currentPiece, gameIsRunning);

    while (gameIsRunning)
    {
        handler.processInput();

        updateGame();

        graphics.clearAndPresentFrame();
    }
}

void Tetris::updateGame()
{
    using namespace TetrisBoard;

    for (Point point : currentPiece.getOldCoordinates())
         Grid::set(point.getX(), point.getY(), '#');

    for (Point point : currentPiece.getNewCoordinates())
         Grid::set(point.getX(), point.getY(), currentPiece.getType());
}
