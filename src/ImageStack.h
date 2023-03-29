#pragma once
#include "IUndoListener.h"
#include <vector>
#include <memory>
#include <wx/bitmap.h>

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > undoBuffer;
	std::vector<std::shared_ptr<wxBitmap> > redoBuffer;
	wxBitmap *savedBitmap = NULL;
	IUndoListener *undoListener = NULL;

public:
	std::shared_ptr<wxBitmap> getImage();
	void init(std::shared_ptr<wxBitmap> bmp);
	void pushImage(std::shared_ptr<wxBitmap> bmp);
	void redo();
	void undo();
	void markSaved();
	bool isModified();
	void setUndoListener(IUndoListener *ul);
};
