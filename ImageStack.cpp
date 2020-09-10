#include "ImageStack.h"

ImageStack::ImageStack(std::shared_ptr<wxBitmap> bmp) {
	buffer.push_back(bmp);
}

std::shared_ptr<wxBitmap> ImageStack::getImage() {
	if (activeBmp == NULL) {
		activeBmp = std::shared_ptr<wxBitmap>(new wxBitmap(*buffer.back()));
	}
	return activeBmp;
}
