#pragma once
#include <vector>
#include <memory>
#include <wx/bitmap.h>

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > undoBuffer;
	std::vector<std::shared_ptr<wxBitmap> > redoBuffer;
	wxBitmap *savedBitmap = NULL;

public:
	std::shared_ptr<wxBitmap> getImage();
	void clear();
	void init(std::shared_ptr<wxBitmap> bmp);
	void pushImage(std::shared_ptr<wxBitmap> bmp);
	void redo();
	void popImage();
	void markSaved();
	bool isModified();
};
