#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include "core/game-state.hpp"

class EventHandler {
public:
	void handleEvent(const SDL_Event& event, bool& quit, GameState& state);

private:
	void handleInput(const SDL_Event& event, GameState& state);
};

#endif
