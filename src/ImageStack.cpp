#include "ImageStack.h"
#include <iostream>

std::shared_ptr<wxBitmap> ImageStack::getImage() {
	return undoBuffer.back();
}

void ImageStack::clear() {
	undoBuffer.clear();
}

void ImageStack::init(std::shared_ptr<wxBitmap> bmp) {
	if (!undoBuffer.empty() || !redoBuffer.empty()) {
		std::cerr << "ImageStack::init - warning: buffers not empty";
	}
	undoBuffer.clear();
	redoBuffer.clear();
	undoBuffer.push_back(bmp);
	markSaved();
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

void ImageStack::markSaved() {
	savedBitmap = undoBuffer.back().get();
}

bool ImageStack::isModified() {
	return savedBitmap != undoBuffer.back().get();
}
