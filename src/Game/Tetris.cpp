#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <cstdlib>

#include "Tetris.hpp"

#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include "../api/SDL-Subsystems.hpp"


Tetris::Tetris()
{
    /* GameCore initializes SDL subsystems such as SDL_Render
     * and SDL_window.
     *
     * GraphicsModule will use the renderer to draw on the screen.
     *
     * Eventhandler will handle SDL events and Player movement.
     * */
    SDL_Subsystems core;

    Graphics graphics =
        Graphics(core.renderer(),
                 core.font(),
                 m_piece);

    EventHandler handler = EventHandler(&m_piece,
                                        m_running);
    
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
}

void Tetris::updateGame()
{
    Mechanics::checkFullRow(m_points);

    if (m_points > 20) m_difficulty = NORMAL;
    else if (m_points > 50) m_difficulty = HARD;
  
    Mechanics::invokeGravity(&m_piece, m_timer, m_difficulty);
    
    m_piece.draw();
}
