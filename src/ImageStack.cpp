#include "ImageStack.h"

std::shared_ptr<wxBitmap> ImageStack::getImage() {
	return undoBuffer.back();
}

void ImageStack::clear() {
	undoBuffer.clear();
}

void ImageStack::pushImage(std::shared_ptr<wxBitmap> bmp) {
	undoBuffer.push_back(bmp);
	redoBuffer.clear();
}

void ImageStack::redo() {
	if (redoBuffer.size() > 0) {
		undoBuffer.push_back(redoBuffer.back());
		redoBuffer.pop_back();
	}
}

void ImageStack::popImage() {
	if (undoBuffer.size() > 1) {
		redoBuffer.push_back(undoBuffer.back());
		undoBuffer.pop_back();
	}
}
