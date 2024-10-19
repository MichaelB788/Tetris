#include <SDL2/SDL.h>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "Objects/Board.hpp"
#include "Objects/Piece.hpp"

char piecetypes[7] = {'I','O','T','S','Z','L','J'};

void Tetris::runGame(GraphicsModule gm)
{
    while (gameIsRunning)
    {
        EventHandler::processInput(event, gameIsRunning);

        gm.clearAndPresentFrame(board);
    }
}
