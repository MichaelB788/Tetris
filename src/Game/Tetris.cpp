#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "Objects/Piece.hpp"

void Tetris::runGame(GraphicsModule graphics)
{
    EventHandler handler = EventHandler(&m_player, m_gameIsRunning);

    while (m_gameIsRunning)
    {
        handler.processInput();

        updateGame();

        graphics.clearAndPresentFrame();
    }
}

void Tetris::updateGame()
{
    Piece target = m_player.getPiece();

    target.modifyGrid();
}
