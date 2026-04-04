#include "platform/EventHandler.hpp"
#include "core/TetrisGame.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

namespace {
constexpr std::array<std::pair<std::string_view, EventHandler::Command>, 7>
    string_to_command{{{"move_left", &TetrisGame::move_left},
                       {"move_down", &TetrisGame::move_down},
                       {"move_right", &TetrisGame::move_right},
                       {"rotate_clockwise", &TetrisGame::rotate_cw},
                       {"rotate_counterclockwise", &TetrisGame::rotate_ccw},
                       {"hold", &TetrisGame::hold},
                       {"drop", &TetrisGame::drop}}};

constexpr std::array<std::pair<SDL_Keycode, EventHandler::Command>, 7>
    default_controls{{{SDLK_LEFT, &TetrisGame::move_left},
                      {SDLK_DOWN, &TetrisGame::move_down},
                      {SDLK_RIGHT, &TetrisGame::move_right},
                      {SDLK_R, &TetrisGame::rotate_cw},
                      {SDLK_E, &TetrisGame::rotate_ccw},
                      {SDLK_S, &TetrisGame::hold},
                      {SDLK_SPACE, &TetrisGame::drop}}};
} // namespace

EventHandler::EventHandler(const std::filesystem::path &config_path)
    : controls_{default_controls} {
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
auto find_value(const auto &key, const std::array<std::pair<K, V>, N> &map)
    -> const V * {
  for (const auto &[k, v] : map) {
    if (key == k)
      return &v;
  }
  return nullptr;
}
} // namespace

void EventHandler::handle_event(TetrisGame &tetris, SDL_Window &window, int &w,
                                int &h) {
  while (SDL_PollEvent(&sdl_event_)) {
    switch (sdl_event_.type) {
    case SDL_EVENT_QUIT:
      should_quit_ = true;
      break;
    case SDL_EVENT_WINDOW_RESIZED:
      SDL_GetWindowSizeInPixels(&window, &w, &h);
      break;
    case SDL_EVENT_KEY_DOWN:
      if (const auto command = find_value(sdl_event_.key.key, controls_))
        (tetris.**command)();
      break;
    default:
      break;
    }
  }
}

void EventHandler::parse_controls(std::istream &input) {
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

    const auto input_name = current_line.substr(0, eq_pos);
    if (const auto command = find_value(input_name, string_to_command)) {
      const auto keycode_name = current_line.substr(eq_pos + 1);
      const auto keycode = SDL_GetKeyFromName(keycode_name.c_str());
      controls_[i++] = {keycode, *command};
    } else {
      std::cerr << "Warn: Could not detect command from string '" << input_name
                << "'. Using default controls\n";
      controls_ = default_controls;
      return;
    }
  }
}
