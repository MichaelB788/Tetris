#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
BUILD_DIR="$PROJECT_ROOT/build"

CMAKE_OPTS=(
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
  "-DCMAKE_BUILD_TYPE=Debug"
  "-G Ninja")
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" "${CMAKE_OPTS[@]}"

ninja -C "$BUILD_DIR"
