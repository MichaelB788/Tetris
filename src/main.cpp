#include "core/TetrisApp.hpp"
#include "platform/PlatformSDL.hpp"
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

std::filesystem::path get_binary_path() {
#ifdef _WIN32
  wchar_t path[MAX_PATH];
  GetModuleFileNameW(nullptr, path, MAX_PATH);
  return std::filesystem::path(path);
#elif defined(__APPLE__)
  char path[1024];
  uint32_t size = sizeof(path);
  _NSGetExecutablePath(path, &size);
  return std::filesystem::canonical(path);
#elif defined(__linux__)
  return std::filesystem::canonical("/proc/self/exe");
#endif
}

int main() {
  using namespace std::literals::chrono_literals;

  std::filesystem::path project_root = get_binary_path();
  for (int i = 0; i < 3; ++i)
    project_root = project_root.parent_path();

  try {
    PlatformSDL platform{};

    TetrisApp tetris(
        {.controls = project_root / "controls.ini",
         .tetromino_atlas =
             project_root / "assets" / "sprites" / "tetromino.png",
         .font_path = project_root / "assets" / "font" / "Arcade-Classic.ttf",
         .font_size = 36});

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
