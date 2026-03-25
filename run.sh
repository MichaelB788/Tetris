#!/usr/bin/env bash

set -euo pipefail

run() {
  local project_root
  project_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
  local build_dir="${project_root}/build"

  local cmake_opts=(
    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    "-DCMAKE_BUILD_TYPE=Debug"
  )

  cmake -S "${project_root}" -B "${build_dir}" "${cmake_opts[@]}" -G Ninja
  ninja -C "${build_dir}"

  local exe="${build_dir}/bin/Tetris"

  "$exe"
}

run
