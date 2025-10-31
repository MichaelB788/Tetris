#include "app/tetris.hpp"

enum Screen {
  WIDTH = 600,
  HEIGHT = 600
};

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

void Tetris::gameLoop() {
  Tetromino piece = Tetromino();
  Matrix playfield;
  SDL_Event event;
  bool quit = false;

  while (quit == false) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				// event_handler::handle(event, piece, playfield);
			}
    }
  }
}

Tetris::Tetris()
{
  initSDL();

	gameLoop();

  closeSDL();
}
