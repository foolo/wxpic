# Prerequisites

	sudo apt install libwxgtk3.0-gtk3-dev

# Building

	meson build
	cd build
	ninja

# Create snap

	snapcraft

or

	snapcraft remote-build --build-for=amd64

# Running

	cd build
	./wxpic FILENAME

# Update icon

	xxd --include res/crosshair.png > src/image_data.h
