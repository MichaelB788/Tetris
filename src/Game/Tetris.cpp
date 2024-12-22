#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"
#include "../Components/Commands/Move.hpp"

#include "../API/GameCore.hpp"

#include "Objects/Grid.hpp"
#include "Objects/Piece.hpp"

Tetris::Tetris()
{
    /* GameCore initializes SDL subsystems such as SDL_Render
     * and SDL_window.
     *
     * GraphicsModule will use the renderer to draw on the screen.
     *
     * Eventhandler will handle SDL events and Player movement.
     * */
    GameCore core;
    GraphicsModule graphics = GraphicsModule(core.m_Renderer);
    EventHandler handler = EventHandler(&m_piece, m_running);
    
    m_piece.draw();

    // Game loop
    while (m_running)
    {
        m_timer++;

        handler.processInput();

        updateGame();
        
        graphics.clearAndPresentFrame();
            
        SDL_Delay(5);
    }

    std::cout << "Points earned: " << m_points << std::endl;
    // Testing
    Grid::printGrid();
}

void Tetris::updateGame()
{
    checkForFullRow();
  
    invokeGravity();
    
    m_piece.draw();
}

void Tetris::invokeGravity()
{
    if (m_points > 20) m_difficulty = NORMAL;
    else if (m_points > 50) m_difficulty = HARD;

    if (m_timer % m_difficulty == 0)
        MoveCommand(&m_piece, DOWN).execute();
}

void Tetris::checkForFullRow()
{
    for (int row = 0; row < 22; row++)
    {
        if (Grid::hasFullRow(row))
        { 
            Grid::clear(row);
            m_points++;   
        }
    }
}
