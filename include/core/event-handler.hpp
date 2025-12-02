#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string_view>
#include "util/flat-array-map.hpp"
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
	
	EventHandler(const std::string& controlsConfigPath) { parseControlsConfig(controlsConfigPath); };

	void handle(const SDL_Event& event, GameState& gameState, bool& quit);

private:
	void executeCommand(Command command, GameState& gameState) const;

	const std::filesystem::path* findFilePath(const std::string& filename) const;

	bool parseControlsConfig(const std::string& filename);

private:
	using enum EventHandler::Command;
	static constexpr FlatArrayMap<std::string_view, EventHandler::Command, 7> commandFromString {
		{ "move_left", MOVE_LEFT },
		{ "move_down", MOVE_DOWN },
		{ "move_right", MOVE_RIGHT },
		{ "rotate_clockwise", ROTATE_CLOCKWISE },
		{ "rotate_counterclockwise", ROTATE_COUNTERCLOCKWISE },
		{ "hold", HOLD },
		{ "drop", DROP }
	};
	FlatArrayMap<SDL_Keycode, Command, 7> inputToCommand;
};

#endif
