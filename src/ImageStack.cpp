#include "ImageStack.h"

std::shared_ptr<wxBitmap> ImageStack::getImage() {
	return buffer.back();
}

void ImageStack::clear() {
	buffer.clear();
}

void ImageStack::pushImage(std::shared_ptr<wxBitmap> bmp) {
	buffer.push_back(bmp);
}

void ImageStack::popImage() {
	if (buffer.size() > 1) {
		buffer.pop_back();
	}
}
