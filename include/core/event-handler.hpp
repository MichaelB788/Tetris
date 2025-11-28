#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "core/game-state.hpp"

class EventHandler {
public:
	enum class Command : uint8_t {
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_DOWN,
		ROTATE_CLOCKWISE,
		ROTATE_COUNTERCLOCKWISE,
		HOLD,
		DROP
	};
	
	EventHandler(const std::string& controlsConfigPath) {
		initializeInputToCommandMap(); parseControlsConfig(controlsConfigPath);
	};

	void handle(const SDL_Event& event, GameState& gameState, bool& quit);

private:
	void executeCommand(Command command, GameState& gameState) const;
	bool parseControlsConfig(const std::string& filename);
	static void initializeInputToCommandMap();

private:
	static std::unordered_map<std::string, Command> commandFromString;
	std::unordered_map<SDL_Keycode, Command> inputToCommand;
};

#endif
