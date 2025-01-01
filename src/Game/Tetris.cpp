#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

#include "Tetris.hpp"
#include "Mechanics.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

Tetris::Tetris() : m_piece(Piece(Mechanics::assignTile()))
{
    /* GameCore initializes SDL subsystems such as SDL_Render
     * and SDL_window.
     *
     * GraphicsModule will use the renderer to draw on the screen.
     *
     * Eventhandler will handle SDL events and Player movement.
     * */
    Graphics graphics =
        Graphics(m_core.m_renderer, m_piece);

    EventHandler handler = EventHandler(&m_piece);
    
    m_piece.draw();

    // Game loop
    while (m_event.type != SDL_QUIT &&
           m_event.key.keysym.sym != SDLK_q)
    {
        m_timer++;

        if (SDL_PollEvent(&m_event))
            handler.processInput(m_event);

        updateGame();
        
        graphics.clearAndPresentFrame();
            
        SDL_Delay(5);
    }

    std::cout << "Points earned: " << m_points << std::endl;
}

void Tetris::updateGame()
{
    Mechanics::checkFullRow(m_points);

    if (m_points > 20) m_difficulty = NORMAL;
    else if (m_points > 50) m_difficulty = HARD;
  
    Mechanics::invokeGravity(&m_piece, m_timer, m_difficulty);
    
    m_piece.draw();
}
