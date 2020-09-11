#pragma once
#include "ImageStack.h"
#include "ITool.h"

class ShapeTool : public ITool {
	ImageStack *imageStack;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;

public:
	ShapeTool(ImageStack *imageStack);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseUp(wxPoint pos);
	wxBitmap *getPreview();
};
