#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "Objects/Coordinate.hpp"
#include "Objects/Grid.hpp"
#include "Objects/Piece.hpp"

void Tetris::runGame(GraphicsModule graphics)
{
    EventHandler handler = EventHandler(&m_currentPiece, m_gameIsRunning);
    while (m_gameIsRunning)
    {
        handler.processInput();

        updateGame();

        graphics.clearAndPresentFrame();
    }
}

void Tetris::updateGame()
{
    for (Point& point : m_currentPiece.getOldCoordinates())
         Grid::set(point, '#');

    for (Point& point : m_currentPiece.getNewCoordinates())
         Grid::set(point, m_currentPiece.getType());
}
