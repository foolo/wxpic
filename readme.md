# Prerequisites

	sudo apt install libwxgtk3.0-gtk3-dev
	sudo apt install libwebp-dev
	sudo apt install libboost-dev

# Building

	meson builddir
	cd builddir
	ninja

# Create snap

	snapcraft

or

	snapcraft remote-build --build-for=amd64

# Running

	cd builddir
	./wxpic FILENAME

# Update image data

	util/files-to-h.py res/crosshair.png res/icons/* > src/image_data.h

# Local install

Create `~/.local/share/applications/wxpic_dev.desktop` with the content below. Replace WXPIC_REPO_PATH with the path to the wxPic repository.

	[Desktop Entry]
	Type=Application
	Name=wxPic dev
	GenericName=Image Editor
	Comment=Minimal image editor
	Icon=WXPIC_REPO_PATH/snap/gui/wxpic.png
	Exec=WXPIC_REPO_PATH/builddir/wxpic %U
	MimeType=image/jpeg;image/jpg;image/pjpeg;image/png;image/x-png;image/webp;
	Categories=Graphics;2DGraphics;
	Keywords=draw;drawing;paint;painting;graphics;2d;
	StartupNotify=true

Run

	update-desktop-database ~/.local/share/applications
