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
