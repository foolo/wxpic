#pragma once

#include <vector>
#include <memory>
#include <wx/bitmap.h>

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > buffer;

public:
	ImageStack(std::shared_ptr<wxBitmap> bmp);
	std::shared_ptr<wxBitmap> getImage();
	void pushImage(std::shared_ptr<wxBitmap> bmp);
};
