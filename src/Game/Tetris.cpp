#include <SDL2/SDL.h>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "Objects/TetrisBoard.hpp"

void Tetris::runGame(GraphicsModule gm)
{
    TetrisBoard::Piece p;

    while (gameIsRunning)
    {
        EventHandler::processInput(event, gameIsRunning);

        gm.clearAndPresentFrame();
    }
}
