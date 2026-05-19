#include "platform/EventHandler.hpp"
#include "core/TetrisGame.hpp"
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <string>

EventHandler::EventHandler(const std::filesystem::path &config_path) {
  if (config_path.empty()) {
    std::cerr << "Using default controls.\n";
    return;
  }

  if (!std::filesystem::exists(config_path) ||
      config_path.filename() != "controls.ini") {
    std::cerr << "Warn: expected file \"controls.ini\", instead got "
              << config_path.filename() << "\n";
    return;
  }

  std::ifstream config_file(config_path);
  if (!config_file.is_open()) {
    std::cerr << "Warn: Unable to open the config file.\n";
    return;
  }

  parse_controls(config_file);
}

namespace {
template <typename K, typename V, size_t N>
auto find_value(const auto &key, const std::array<std::pair<K, V>, N> &map)
    -> std::optional<V> {
  for (const auto &[k, v] : map) {
    if (key == k)
      return v;
  }
  return std::nullopt;
}
} // namespace

void EventHandler::handle_kb_input(Tetris &tetris, std::mt19937 &rng,
                                   std::chrono::nanoseconds delta) {
  auto curr_kb_state = SDL_GetKeyboardState(nullptr);

  for (const auto &[scancode, command] : controls_) {
    auto execute_input = [&] { tetris.invoke_action(command, rng); };
    if (!prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      // First key press
      tetris.invoke_action(command, rng);
      movement_.init_delay.reset();
      rotation_.init_delay.reset();
    } else if (prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      // Key is held down
      using enum Tetris::Action;
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
  }

  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_kb_state_[i] = curr_kb_state[i];
  }
}

void EventHandler::parse_controls(std::istream &input) {
  using enum Tetris::Action;
  static constexpr std::array<std::pair<std::string_view, Tetris::Action>, 8>
      STR_TO_FUNC{{{"move_left", MoveLeft},
                   {"move_right", MoveRight},
                   {"soft_drop", SoftDrop},
                   {"hard_drop", HardDrop},
                   {"rotate_clockwise", RotateClockwise},
                   {"rotate_counterclockwise", RotateCounterclockwise},
                   {"rotate_half_turn", RotateHalf},
                   {"hold", Hold}}};

  const auto default_controls = controls_;

  size_t i = 0;
  std::string current_line;
  while (std::getline(input, current_line)) {
    const auto first = current_line.find_first_not_of(" \t");
    if (std::string::npos == first) {
      continue;
    }

    const auto last = current_line.find_last_not_of(" \t");
    current_line = current_line.substr(first, (last - first + 1));
    if (current_line.empty() || current_line[0] == ';' ||
        current_line[0] == '#') {
      continue;
    }

    const auto eq_pos = current_line.find('=');
    if (eq_pos == std::string::npos) {
      continue;
    }

    const auto command_str = current_line.substr(0, eq_pos);
    if (const auto command = find_value(command_str, STR_TO_FUNC)) {
      const auto sdl_scancode_str = current_line.substr(eq_pos + 1);
      const auto sdl_scancode =
          SDL_GetScancodeFromName(sdl_scancode_str.c_str());
      controls_[i++] = {sdl_scancode, command.value()};
    } else {
      std::cerr << "Warn: Could not detect command from string '" << command_str
                << "'. Using default controls\n";
      controls_ = default_controls;
      return;
    }
  }
}
