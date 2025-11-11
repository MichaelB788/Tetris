#include "core/event-handler.hpp"

void EventHandler::handleInput(SDL_Event& event, GameState& gameState)
{
	switch (event.key.keysym.sym)
	{
		// handle input
		case SDLK_h:
			gameState.moveActor(Vector2::Horizontal::LEFT);
			break;
		case SDLK_l:
			gameState.moveActor(Vector2::Horizontal::RIGHT);
			break;
		case SDLK_j:
			gameState.moveActorDown();
			break;
		case SDLK_r:
			gameState.rotateActor(Vector2::Rotation::CLOCKWISE);
			break;
		case SDLK_t:
			gameState.rotateActor(Vector2::Rotation::COUNTERCLOCKWISE);
			break;
		case SDLK_s:
			gameState.swapActorWithStored();
			break;
		case SDLK_SPACE:
			gameState.dropActor();
			break;
		default:
			break;
	}
}
