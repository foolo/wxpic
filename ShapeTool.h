#pragma once
#include "IImageSource.h"
#include "ITool.h"

class ShapeTool : public ITool {
	IImageSource *imageSource;
	wxPoint startPos;
	std::unique_ptr<wxBitmap> preview;

public:
	ShapeTool(IImageSource *imageSource);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseUp(wxPoint pos);
	wxBitmap *getPreview();
};
