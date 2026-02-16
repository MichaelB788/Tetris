#include "EventHandler.hpp"
#include "Common.hpp"
#include "Tetris.hpp"
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
    string_to_command{
        {{"move_left", &Tetris::move_left},
         {"move_down", &Tetris::move_down},
         {"move_right", &Tetris::move_right},
         {"rotate_clockwise", &Tetris::rotate_clockwise},
         {"rotate_counterclockwise", &Tetris::rotate_counterclockwise},
         {"hold", &Tetris::hold},
         {"drop", &Tetris::drop}}};

constexpr std::array<std::pair<SDL_Keycode, EventHandler::Command>, 7>
    default_controls{{{SDLK_LEFT, &Tetris::move_left},
                      {SDLK_DOWN, &Tetris::move_down},
                      {SDLK_RIGHT, &Tetris::move_right},
                      {SDLK_R, &Tetris::rotate_clockwise},
                      {SDLK_E, &Tetris::rotate_counterclockwise},
                      {SDLK_S, &Tetris::hold},
                      {SDLK_SPACE, &Tetris::drop}}};
} // namespace

EventHandler::EventHandler(std::optional<std::filesystem::path> config)
    : controls_{default_controls} {
  if (config.has_value())
    parse_controls_config(config.value());
}

void EventHandler::handle_event(Tetris &tetris) {
  while (SDL_PollEvent(&sdl_event_)) {
    switch (sdl_event_.type) {
    case SDL_EVENT_QUIT:
      should_quit_ = true;
      break;
    case SDL_EVENT_WINDOW_RESIZED:
      // SDL_GetWindowSizeInPixels(window, &window_size.w, &window_size.h);
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

void EventHandler::parse_controls_config(
    const std::filesystem::path &path_to_conf) {
  if (path_to_conf.filename() != "controls.ini") {
    std::cerr << "Warning: expected file \"controls.ini\", instead got "
              << path_to_conf.filename() << " Using default controls. \n";
    return;
  }

  std::ifstream config_file(path_to_conf);
  if (!config_file.is_open()) {
    std::cerr
        << "Warning: Unable to open the config file. Using default controls.\n";
    return;
  }

  std::size_t i = 0;
  std::string current_line;
  while (std::getline(config_file, current_line)) {
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
