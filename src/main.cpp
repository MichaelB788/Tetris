// SDL2 Library
#include <SDL2/SDL.h>

// C++ Libraries
#include <iostream>

// SDL Classes
#include "SDL/Window.hpp"
#include "SDL/Render.hpp"

// Game Objects
#include "Game/Piece.hpp"
#include "Game/Board.hpp"

// Custom Components
#include "Components/Graphics.hpp"
#include "Components/EventHandler.hpp"

int main (int argc, char **argv)
{
    // Initialize all SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Could not initialize SDL Video: " << SDL_GetError() << std::endl;
        return 1; 
    }

    // Initialize SDL window and renderer.
    const WindowObject WIN = WindowObject();
    const RendererObject REN = RendererObject(WIN.pSDL_Window);

    if (WIN.pSDL_Window == NULL || REN.pSDL_Renderer == NULL)
    {
        return 1;
    }

    bool gameIsRunning = true;
    SDL_Event event;

    const char piecetypes[7] = {'I','O','T','S','Z','L','J'};
    // Game loop
    while (gameIsRunning)
    {
        // Handle the events
        EventHandler::process(event, gameIsRunning);

        // Clear the screen
        SDL_RenderClear(REN.pSDL_Renderer);

        // Draw our new frame
        Graphics::renderFrame(Board::board_state, REN.pSDL_Renderer);

        // Show our new frame
        SDL_RenderPresent(REN.pSDL_Renderer); 
    }
    
    SDL_Quit();

    return 0;
}
