#include "platform/EventHandler.hpp"
#include "core/TetrisGame.hpp"
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

EventHandler::EventHandler(TetrisGame &game,
                           const std::filesystem::path &config_path)
    : tetris_(game) {
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
  requires std::is_member_function_pointer_v<V>
auto find_func_ptr(const auto &key, const std::array<std::pair<K, V>, N> &map)
    -> V {
  for (const auto &[k, v] : map) {
    if (key == k)
      return v;
  }
  return nullptr;
}
} // namespace

void EventHandler::handle_kb_input(std::chrono::nanoseconds delta) {
  auto curr_kb_state = SDL_GetKeyboardState(nullptr);

  for (const auto &[scancode, func] : controls_) {
    if (!prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      // First key press
      (tetris_.*func)();
      delay_until_rapid_fire_.reset();
    } else if (prev_kb_state_[scancode] && curr_kb_state[scancode]) {
      // Key is held down
      delay_until_rapid_fire_ += delta;
      if (delay_until_rapid_fire_.has_set_off()) {
        rapid_fire_delay_.tick(delta, [&] { (tetris_.*func)(); });
      }
    }
  }

  for (size_t i = 0; i < SDL_SCANCODE_COUNT; ++i) {
    prev_kb_state_[i] = curr_kb_state[i];
  }
}

void EventHandler::parse_controls(std::istream &input) {
  static constexpr std::array<std::pair<std::string_view, Command>, 8>
      STR_TO_FUNC{{{"move_left", &TetrisGame::move_left},
                   {"move_right", &TetrisGame::move_right},
                   {"soft_drop", &TetrisGame::soft_drop},
                   {"hard_drop", &TetrisGame::hard_drop},
                   {"rotate_clockwise", &TetrisGame::rotate_cw},
                   {"rotate_counterclockwise", &TetrisGame::rotate_ccw},
                   {"rotate_half_turn", &TetrisGame::rotate_ht},
                   {"hold", &TetrisGame::hold}}};

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
    if (const auto command = find_func_ptr(command_str, STR_TO_FUNC)) {
      const auto sdl_scancode_str = current_line.substr(eq_pos + 1);
      const auto sdl_scancode =
          SDL_GetScancodeFromName(sdl_scancode_str.c_str());
      controls_[i++] = {sdl_scancode, command};
    } else {
      std::cerr << "Warn: Could not detect command from string '" << command_str
                << "'. Using default controls\n";
      controls_ = default_controls;
      return;
    }
  }
}
