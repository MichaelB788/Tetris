#include "core/event-handler.hpp"

void EventHandler::handleInput(SDL_Event& event, TetrominoController& controller)
{
	switch (event.key.keysym.sym)
	{
		// handle input
		case SDLK_h:
			controller.moveActor(Direction::Horizontal::LEFT);
			break;
		case SDLK_l:
			controller.moveActor(Direction::Horizontal::RIGHT);
			break;
		case SDLK_j:
			controller.moveActorDown();
			break;
		case SDLK_r:
			controller.rotateActor(Direction::Rotation::CLOCKWISE);
			break;
		case SDLK_t:
			controller.rotateActor(Direction::Rotation::COUNTERCLOCKWISE);
			break;
		case SDLK_s:
			//controller.swapActorWithStored();
			break;
		case SDLK_SPACE:
			controller.dropActor();
			break;
		default:
			break;
	}
}
