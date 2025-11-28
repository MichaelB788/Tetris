#include "core/event-handler.hpp"

std::unordered_map<std::string, EventHandler::Command> EventHandler::commandFromString;

void EventHandler::initializeInputToCommandMap() {
	commandFromString.reserve(7);
	using enum EventHandler::Command;
	commandFromString = {
		{ "move_left", MOVE_LEFT },
		{ "move_down", MOVE_DOWN },
		{ "move_right", MOVE_RIGHT },
		{ "rotate_clockwise", ROTATE_CLOCKWISE },
		{ "rotate_counterclockwise", ROTATE_COUNTERCLOCKWISE },
		{ "hold", HOLD },
		{ "drop", DROP },
	};
}

void EventHandler::handle(const SDL_Event& event, GameState& gameState, bool& quit) {
	switch (event.type) {
		case SDL_QUIT:
			quit = true; break;
		case SDL_KEYDOWN:
			if (inputToCommand.find(event.key.keysym.sym) != inputToCommand.end())
				executeCommand(inputToCommand[event.key.keysym.sym], gameState);
			break;
		default: break;
	}
}

void EventHandler::executeCommand(Command command, GameState& gameState) const {
	using enum Command;
	switch (command) {
		case MOVE_LEFT:
			gameState.moveLeft(); break;
		case MOVE_RIGHT:
			gameState.moveRight(); break;
		case MOVE_DOWN:
			gameState.moveDown(); break;
		case ROTATE_CLOCKWISE:
			gameState.rotateClockwise(); break;
		case ROTATE_COUNTERCLOCKWISE:
			gameState.rotateCounterclockwise(); break;
		case HOLD:
			gameState.hold(); break;
		case DROP:
			gameState.drop(); break;
		default: break;
	}
}

bool EventHandler::parseControlsConfig(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Could not open controls.ini, controls may not work!" << std::endl;
		return false;
	}

	std::string line;
	std::string currentSection;
	inputToCommand.reserve(7);

	while (std::getline(file, line)) {
		size_t first = line.find_first_not_of(" \t");
		if (std::string::npos == first) continue;

		size_t last = line.find_last_not_of(" \t");
		line = line.substr(first, (last - first + 1));

		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		size_t equalsPos = line.find('=');
		if (equalsPos != std::string::npos) {
			SDL_Keycode keycode = SDL_GetKeyFromName(line.substr(equalsPos + 1).c_str());
			EventHandler::Command command = commandFromString.at(line.substr(0, equalsPos));
			inputToCommand[keycode] = command;
		}
	}

	file.close();
	return true;
}
