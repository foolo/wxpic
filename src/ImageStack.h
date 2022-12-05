#pragma once
#include <vector>
#include <memory>
#include <wx/bitmap.h>

class IUndoListener {
public:
	virtual void notify() = 0;
	virtual ~IUndoListener() {}
};

class ImageStack {
	std::vector<std::shared_ptr<wxBitmap> > undoBuffer;
	std::vector<std::shared_ptr<wxBitmap> > redoBuffer;
	wxBitmap *savedBitmap = NULL;
	IUndoListener *undoListener = NULL;

public:
	std::shared_ptr<wxBitmap> getImage();
	void clear();
	void init(std::shared_ptr<wxBitmap> bmp);
	void pushImage(std::shared_ptr<wxBitmap> bmp);
	void redo();
	void undo();
	void markSaved();
	bool isModified();
	void setUndoListener(IUndoListener *ul);
};
