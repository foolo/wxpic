# Build wxWidgets for static linking

	sudo apt-get install libgtk-3-dev
	git clone --branch v3.2.1 --recurse-submodules https://github.com/wxWidgets/wxWidgets.git
	cd wxWidgets
	mkdir buiddir
	cd buiddir
	cmake .. -DCMAKE_INSTALL_PREFIX=~/wx_install -DwxBUILD_SHARED=OFF
	cmake --build . --target install

# Building

	bash -c "PATH=~/wx_install/bin:$PATH meson builddir"
	cd builddir
	ninja

# Create snap

	// TODO change to static linking in snap/snapcraft.yaml ?
	snapcraft

or

	snapcraft remote-build --build-for=amd64

# Running

	cd builddir
	./wxpic FILENAME

# Update icon

	xxd --include res/crosshair.png > src/image_data.h
