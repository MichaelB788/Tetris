#include <iostream> // for testing
#include "app/tetris.hpp"

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

Tetris::Tetris()
{
  initSDL();

  Tetromino piece = Tetromino(Tetromino::Type::I);
  std::cout << "Hello World!" << std::endl;
  TetrisMatrix playfield;

  SDL_Event e;
  bool quit = false;
  while (quit == false)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }

  closeSDL();
}
