#include "platform/EventHandler.hpp"
#include "core/TetrisGame.hpp"
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

namespace {
constexpr std::array<std::pair<SDL_Scancode, Command>, 7> default_controls{
    {{SDL_SCANCODE_LEFT, &TetrisGame::move_left},
     {SDL_SCANCODE_RIGHT, &TetrisGame::move_right},
     {SDL_SCANCODE_DOWN, &TetrisGame::soft_drop},
     {SDL_SCANCODE_SPACE, &TetrisGame::hard_drop},
     {SDL_SCANCODE_R, &TetrisGame::rotate_cw},
     {SDL_SCANCODE_E, &TetrisGame::rotate_ccw},
     {SDL_SCANCODE_S, &TetrisGame::hold}}};
} // namespace

EventHandler::EventHandler(TetrisGame &game,
                           const std::filesystem::path &config_path)
    : tetris_(game), controls_{default_controls} {
  if (!std::filesystem::exists(config_path)) {
    std::cerr << "Warn: Could not find file: " << config_path.filename()
              << std::endl;
    return;
  }

  if (config_path.filename() != "controls.ini") {
    std::cerr << "Warn: expected file \"controls.ini\", instead got "
              << config_path.filename() << std::endl;
    return;
  }

  std::ifstream config_file(config_path);

  if (!config_file.is_open()) {
    std::cerr << "Warn: Unable to open the config file." << std::endl;
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

void EventHandler::handle_kb_input() {
  const auto current_key_states = SDL_GetKeyboardState(NULL);

  for (const auto &[scancode, func] : controls_) {
    if (current_key_states[scancode]) {
      (tetris_.*func)();
    }
  }
}

void EventHandler::parse_controls(std::istream &input) {
  static constexpr std::array<std::pair<std::string_view, Command>, 7>
      COMMAND_STR_TO_FUNC{{{"move_left", &TetrisGame::move_left},
                           {"move_right", &TetrisGame::move_right},
                           {"soft_drop", &TetrisGame::soft_drop},
                           {"hard_drop", &TetrisGame::hard_drop},
                           {"rotate_clockwise", &TetrisGame::rotate_cw},
                           {"rotate_counterclockwise", &TetrisGame::rotate_ccw},
                           {"hold", &TetrisGame::hold}}};

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
    if (const auto command = find_func_ptr(command_str, COMMAND_STR_TO_FUNC)) {
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
