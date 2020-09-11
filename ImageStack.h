#pragma once

#include <vector>
#include <memory>
#include <wx/bitmap.h>

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > buffer;

public:
	std::shared_ptr<wxBitmap> getImage();
	void clear();
	void pushImage(std::shared_ptr<wxBitmap> bmp);
};
