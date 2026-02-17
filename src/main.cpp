#include "PlatformSDL.hpp"
#include "TetrisApp.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <iostream>

std::string path_n_levels_up(unsigned n, boost::filesystem::path path) {
  for (unsigned i = 0; i < n; ++i)
    path = path.parent_path();
  return path.string();
}

int main() {
  using namespace std::literals::chrono_literals;

  std::filesystem::path project_root =
      path_n_levels_up(3, boost::dll::program_location());

  try {
    PlatformSDL platform{};

    TetrisApp tetris(
        {.controls = project_root / "controls.ini",
         .tetromino_atlas = project_root / "assets/sprites/tetromino.png",
         .font_path = project_root / "assets/font/Arcade-Classic.ttf",
         .font_size = 36,
         .gravity_rate = 1000ms});

    tetris.run();
  } catch (const ExceptionSDL &exception) {
    std::cerr << exception.what() << std::endl;
    return EXIT_FAILURE;
  } catch (const std::invalid_argument &exception) {
    std::cerr << "Invalid argument encountered: " << exception.what()
              << std::endl;
    return EXIT_FAILURE;
  } catch (const std::exception &exception) {
    std::cerr << "Encountered exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
