#include "ImageStack.h"

ImageStack::ImageStack(std::shared_ptr<wxBitmap> bmp) {
	buffer.push_back(bmp);
}

std::shared_ptr<wxBitmap> ImageStack::getImage() {
	return buffer.back();
}

void ImageStack::pushImage(std::shared_ptr<wxBitmap> bmp) {
	buffer.push_back(bmp);
}
