#include "core/event-handler.hpp"
#include <iostream>

void EventHandler::handle(const SDL_Event& event, GameState& gameState, bool& quit) {
	switch (event.type) {
		case SDL_QUIT:
			quit = true; break;
		case SDL_KEYDOWN:
			if (inputToCommand.contains(event.key.keysym.sym))
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

const std::filesystem::path* EventHandler::findFilePath(const std::string& filename) const {
	static const std::array<std::filesystem::path, 4> possiblePaths {
		std::filesystem::current_path() / filename,
		std::filesystem::current_path() / ".." / filename,
		std::filesystem::current_path() / ".." / ".." / filename,
		std::filesystem::current_path() / ".." / ".." / ".." / filename,
	};

	for (const auto& path : possiblePaths) {
		if (std::filesystem::exists(path)) return &path;
	}
	return nullptr;
}

bool EventHandler::parseControlsConfig(const std::string& filename) {
	const std::filesystem::path* path = findFilePath(filename);
	std::ifstream file;

	if ( path ) {
		file.open(path->string());
	} else {
		std::cerr << "Could not find the config file in the current directory! Are you outside of the projects root folder?" << std::endl;
		return false;
	}

	if (!file.is_open()) {
		std::cerr << "Could not open controls.ini, controls may not work!" << std::endl;
		return false;
	}

	std::string line;

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
			inputToCommand.insert({keycode, command});
		}
	}

	file.close();
	return true;
}
