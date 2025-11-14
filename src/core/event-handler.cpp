#include "core/event-handler.hpp"

void EventHandler::handleInput(const SDL_Event& event, GameState& state)
{
	switch (event.key.keysym.sym)
	{
		// handle input
		case SDLK_h:
			state.moveLeft();
			break;
		case SDLK_l:
			state.moveRight();
			break;
		case SDLK_j:
			state.moveDown();
			break;
		case SDLK_r:
			state.rotateClockwise();
			break;
		case SDLK_t:
			state.rotateCounterclockwise();
			break;
		case SDLK_s:
			state.swap();
			break;
		case SDLK_SPACE:
			state.drop();
			break;
		default:
			break;
	}
}
