#include "core/event-handler.hpp"

void EventHandler::handleInput(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
		// handle input
		case SDLK_h:
			r_gameState.moveActor(Vector2::Horizontal::LEFT);
			break;
		case SDLK_l:
			r_gameState.moveActor(Vector2::Horizontal::RIGHT);
			break;
		case SDLK_j:
			r_gameState.moveActorDown();
			break;
		case SDLK_r:
			r_gameState.rotateActor(Vector2::Rotation::CLOCKWISE);
			break;
		case SDLK_t:
			r_gameState.rotateActor(Vector2::Rotation::COUNTERCLOCKWISE);
			break;
		case SDLK_s:
			r_gameState.swapActorWithStored();
			break;
		case SDLK_SPACE:
			r_gameState.dropActor();
			break;
		default:
			break;
	}
}
