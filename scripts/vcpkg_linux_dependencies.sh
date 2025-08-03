#!/bin/bash

set -e

DEPENDENCIES=(
	make
	curl
	zip
	unzip
	tar
	pkg-config
	autoconf
	automake
	autoconf-archive
)

# These dependencies seem to be optional, though vcpkg will warn you about it.
XORG_DEPENDENCIES=(
	libx11-dev
	libxft-dev
	libxext-dev
)

WAYLAND_DEPENDENCIES=(
	libwayland-dev
	libxkbcommon-dev
	libegl1-mesa-dev
)

IBUS_DEPENDENCIES=libibus-1.0-dev

sudo apt-get install "${DEPENDENCIES[@]}"
