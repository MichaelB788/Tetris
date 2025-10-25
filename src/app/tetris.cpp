#include <iostream> // for testing
#include "app/tetris.hpp"
#include "core/event-handler.hpp"

bool Tetris::initSDL()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    m_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::WIDTH, Screen::HEIGHT, SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    }
  }

  return success;
}

void Tetris::closeSDL()
{
  SDL_DestroyWindow(m_window);
  m_window = nullptr;

  SDL_Quit();
}

void Tetris::update(Matrix& playfield, Tetromino& player) {
}

Tetris::Tetris()
{
  initSDL();

  // Initialize game assets
  Tetromino piece = Tetromino(tetromino_operation::generateRandomType(), Vector2(5, 5));
  std::cout << "Hello World! I have a " << static_cast<unsigned int>(piece.m_type) << std::endl;
  Matrix playfield;

  // Game loop
  SDL_Event event;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
				quit = true
			}
			else if (event.type == SDL_KEYDOWN) {
				event_handler::handle(event, piece, playfield);
			}
    }
  }

  closeSDL();
}
