#pragma once
#include "IImageSource.h"
#include "ITool.h"

class ShapeTool : public ITool {
	wxPoint startPos;
	IImageSource *imageSource;

public:
	ShapeTool(IImageSource *imageSource);
	void mouseDown(wxPoint pos);
	void mouseUp(wxPoint pos);
};
