#include "Tetris.hpp"

#include <SDL2/SDL.h>

#include "../API/SDLUtils.hpp"
#include "../Components/Graphics.hpp"
#include "../Components/EventHandler.hpp"

#include <array>

/*
 * A 10 x 20 matrix represents the board 
 *
 * The playable area is represented by # sign. Players are
 * free to roam this area
 *
 * Player object will be represented by their piece:
 * I, O, T, S, Z, J, L
 * 
 * */

SDLUtils::WindowObject SDLUtils::window = SDLUtils::WindowObject();

SDLUtils::RendererObject SDLUtils::renderer = SDLUtils::RendererObject(SDLUtils::window.pSDL_Window);

std::array<std::array<char, 10>, 20> board = {{
        {'#', '#', '#', '#', 'L', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'L', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'L', 'L', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} 
    }};

Tetris::Tetris()
{
    while (gameIsRunning)
    {
        // Handle the events
        EventHandler::process(event, gameIsRunning);

        // Clear the screen
        SDL_RenderClear(SDLUtils::renderer.pSDL_Renderer);

        // Update game

        // Draw our new frame
        Graphics::renderFrame(board, SDLUtils::renderer.pSDL_Renderer);

        // Show our new frame
        SDL_RenderPresent(SDLUtils::renderer.pSDL_Renderer); 
    }
}

void Tetris::clearBoard()
{
    for (auto row : board)
        for (auto col : row)
            col = '#';
}
