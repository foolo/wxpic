#include "UndoBuffer.h"

std::shared_ptr<wxBitmap> UndoBuffer::getImage() {
	if (activeBmp == NULL) {
		activeBmp = std::shared_ptr<wxBitmap>(new wxBitmap(*buffer.back()));
	}
	return activeBmp;
}

UndoBuffer::UndoBuffer(std::shared_ptr<wxBitmap> bmp) {
	buffer.push_back(bmp);
}
