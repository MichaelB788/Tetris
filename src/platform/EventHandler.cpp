#include "platform/EventHandler.hpp"
#include "core/TetrisGame.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

namespace {
template <typename K, typename V, std::size_t N>
int find_key_index(const auto &key,
                   const std::array<std::pair<K, V>, N> &span) {
  for (std::size_t i = 0; i < N; ++i) {
    if (span[i].first == key)
      return static_cast<int>(i);
  }
  return -1;
}

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
      if (const int i = find_key_index(sdl_event_.key.key, controls_); i != -1)
        (tetris.*controls_[i].second)();
      break;
    default:
      break;
    }
  }
}

void EventHandler::parse_controls(std::istream &input) {
  std::size_t i = 0;
  std::string current_line;

  while (std::getline(input, current_line)) {
    const std::size_t first = current_line.find_first_not_of(" \t");
    if (std::string::npos == first)
      continue;

    const std::size_t last = current_line.find_last_not_of(" \t");
    current_line = current_line.substr(first, (last - first + 1));

    if (current_line.empty() || current_line[0] == ';' ||
        current_line[0] == '#')
      continue;

    if (const std::size_t equalsPos = current_line.find('=');
        equalsPos != std::string::npos) {
      std::string keycode_name = current_line.substr(equalsPos + 1);
      std::string input_name = current_line.substr(0, equalsPos);

      int i = find_key_index(input_name, string_to_command);

      if (i == -1) {
        std::cerr << "Warning: Could not parse input with the name "
                  << input_name << ". Using default controls\n";
        controls_ = default_controls;
        return;
      }

      SDL_Keycode keycode = SDL_GetKeyFromName(keycode_name.c_str());
      Command command = string_to_command[i].second;

      controls_[i++] = {keycode, command};
    }
  }
}
