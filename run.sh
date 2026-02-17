#!/bin/bash

main() {
  if [[ ("${1}" == "--build") || !( -d ./build/ ) ]]; then
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build -G Ninja
  fi

  (cd build/ && ninja)

  ./build/bin/Tetris
}

main "${1}"
