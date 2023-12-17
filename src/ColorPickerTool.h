#pragma once
#include "ImageStack.h"
#include "ITool.h"
#include "MainWindow.h"

class ColorPickerTool : public ITool {
	ImageStack *imageStack;
	MainWindow* mainWindow;
	bool mouseDownState;

public:
	ColorPickerTool(ImageStack *is, MainWindow* mw);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseLeaving(wxPoint pos);
	void mouseUp(wxPoint pos);
	std::shared_ptr<wxBitmap> getPreview();
	bool busy();
	void resetPreview();
};
