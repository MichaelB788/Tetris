#include "EventHandler.hpp"
#include "Tetris.hpp"
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <string>

auto EventHandler::set_controls_from_file(
    const std::filesystem::path &config_path) -> bool {
  if (config_path.empty()) {
    std::cerr << "No config path given\n";
    return false;
  }

  if (!std::filesystem::exists(config_path) ||
      config_path.filename() != "controls.ini") {
    std::cerr << "Unknown file: " << config_path.filename() << "\n";
    return false;
  }

  std::ifstream config_file(config_path);
  if (!config_file.is_open()) {
    std::cerr << "Unable to open config file: " << config_path.filename()
              << "\n";
    return false;
  }

  return parse_config_file(config_file);
}

void EventHandler::handle_kb_input(Tetris &tetris, std::mt19937 &rng,
                                   std::chrono::nanoseconds delta) {
  // Handle current keyboard inputs
  auto curr_kb_state = SDL_GetKeyboardState(nullptr);
  for (const auto &[scancode, command] : controls_) {
    if (!prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      handle_first_key_press(tetris, command, rng);
    } else if (prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      handle_key_down(tetris, command, rng, delta);
    }
  }

  // Take a snapshot of current keyboard state
  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_kb_state_[i] = curr_kb_state[i];
  }
}

auto find_command_from_str(std::string_view str)
    -> std::optional<Tetris::Command> {
  using enum Tetris::Command;
  static constexpr std::array<std::pair<std::string_view, Tetris::Command>, 8>
      STR_TO_COMMAND{{{"move_left", MoveLeft},
                      {"move_right", MoveRight},
                      {"soft_drop", SoftDrop},
                      {"hard_drop", HardDrop},
                      {"rotate_clockwise", RotateClockwise},
                      {"rotate_counterclockwise", RotateCounterclockwise},
                      {"rotate_half_turn", RotateHalf},
                      {"hold", Hold}}};

  for (auto [name, command] : STR_TO_COMMAND) {
    if (name == str)
      return command;
  }

  return std::nullopt;
}

auto EventHandler::parse_config_file(std::istream &input) -> bool {
  const auto default_controls = controls_;
  size_t i = 0;
  std::string curr;
  while (std::getline(input, curr)) {
    const auto begin = curr.find_first_not_of(" \t");
    const auto end = curr.find_last_not_of(" \t");
    const auto trimmed = curr.substr(begin, (end - begin + 1));
    const auto eq_pos = trimmed.find('=');
    if (eq_pos == std::string::npos)
      continue;

    const auto command_str = trimmed.substr(0, eq_pos);
    const auto command = find_command_from_str(command_str);
    if (!command) {
      std::cerr << "Unknown command: '" << command_str << "\n";
      controls_ = default_controls;
      return false;
    }

    const auto sdl_scancode_str = trimmed.substr(eq_pos + 1);
    const auto sdl_scancode = SDL_GetScancodeFromName(sdl_scancode_str.c_str());
    if (sdl_scancode == SDL_SCANCODE_UNKNOWN) {
      std::cerr << "Unknown scancode: '" << sdl_scancode_str << "\n";
      controls_ = default_controls;
      return false;
    }

    controls_[i++] = {sdl_scancode, command.value()};
  }

  return true;
}

void EventHandler::handle_first_key_press(Tetris &tetris,
                                          Tetris::Command command,
                                          std::mt19937 &rng) {
  tetris.invoke_command(command, rng);
  movement_.init_delay.reset();
  rotation_.init_delay.reset();
}

void EventHandler::handle_key_down(Tetris &tetris, Tetris::Command command,
                                   std::mt19937 &rng,
                                   std::chrono::nanoseconds delta) {
  using enum Tetris::Command;
  auto execute_input = [&] { tetris.invoke_command(command, rng); };
  if (command == RotateClockwise || command == RotateCounterclockwise ||
      command == RotateHalf) {
    rotation_.init_delay.invoke_when_elapsed(delta, [&] {
      rotation_.repeat_interval.invoke_periodically(delta, execute_input);
    });
  } else {
    movement_.init_delay.invoke_when_elapsed(delta, [&] {
      movement_.repeat_interval.invoke_periodically(delta, execute_input);
    });
  }
}
