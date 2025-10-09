#!/bin/bash
set -e

if [ -f /etc/os-release ]; then
  . /etc/os-release
  OS_FAMILY="${ID_LIKE:-$ID}"
  case "$OS_FAMILY" in
    *debian*) 
      INSTALL="sudo apt-get install -y"
      SDL=(libsdl2-dev libsdl2-2.0-0)
      ;;
    *arch*)
      INSTALL="sudo pacman -S --noconfirm"
      SDL=sdl2
      ;;
    *fedora*)
      INSTALL="sudo dnf install -y"
      SDL=SDL2-devel
      ;;
    *)
      echo "This script isn't supported with this Linux distro: $ID"
      exit 1
  esac
else
  echo "Cannot determine the operating system using /etc/os-release. This script may not be compatible."
  exit 1
fi

PROJECT_DEPENDENCIES=(sdl)