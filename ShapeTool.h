#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"

class ShapeTool : public ITool {
	ImageStack *imageStack;
	ImagePanel* imagePanel;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;

public:
	ShapeTool(ImageStack *imageStack, ImagePanel* imagePanel);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseUp(wxPoint pos);
	wxBitmap *getPreview();
};
