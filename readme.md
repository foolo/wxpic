# Prerequisites

	sudo apt install libwxgtk3.0-gtk3-dev

# Building

	meson build
	cd build
	ninja

# Create snap

	snapcraft

# Running

	cd build
	./wxpic FILENAME

# Update icon

	xxd --include res/crosshair.png > src/image_data.h
