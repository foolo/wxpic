#pragma once

#include <vector>
#include <memory>
#include <wx/bitmap.h>

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > buffer;
	std::shared_ptr<wxBitmap> activeBmp;

public:
	ImageStack(std::shared_ptr<wxBitmap> bmp);
	std::shared_ptr<wxBitmap> getImage();
};
