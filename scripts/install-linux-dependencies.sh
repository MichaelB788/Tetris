#!/bin/bash
set -e

set_os_specific_variables() {
	if [ -f /etc/os-release ]; then
		. /etc/os-release
		OS_FAMILY="${ID_LIKE:-$ID}"
		case "$OS_FAMILY" in
			*debian*) 
				SDL_DEP=(libsdl2-dev libsdl2-2.0-0)
				CATCH_2=catch2
				;;
			*arch*)
				SDL_DEP=(sdl2)
				CATCH_2=catch2
				;;
			*fedora*)
				SDL_DEP=(SDL2-devel)
				CATCH_2=catch2-devel
				;;
			*)
				echo "This script isn't supported with this Linux distro: $ID"
				exit 1
				;;
		esac
	else
		echo "Cannot determine the operating system using /etc/os-release. This script may not be compatible."
		exit 1
	fi
}

install_package() {
	if command -v apt-get &> /dev/null; then
		for arg in "$@"; do
			sudo apt-get install $arg
		done
	elif command -v pacman &> /dev/null; then
		for arg in "$@"; do
			sudo pacman -S $arg
		done
	elif command -v dnf &> /dev/null; then
		for arg in "$@"; do
			sudo dnf $arg
		done
	fi
}

install_all_packages() {
	install_package "${SDL_DEP[@]}"
	install_package $CATCH_2
}

set_os_specific_variables
install_all_packages
