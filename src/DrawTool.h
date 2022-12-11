#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"
#include "MainWindow.h"

class DrawTool : public ITool {
	ImageStack *imageStack;
	MainWindow* mainWindow;
	wxPoint lastMousePos;
	std::shared_ptr<wxBitmap> preview;

public:
	DrawTool(ImageStack *is, MainWindow* mw);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseLeaving(wxPoint pos);
	void mouseUp(wxPoint pos);
	std::shared_ptr<wxBitmap> getPreview();
	bool busy();
	void resetPreview();
};
