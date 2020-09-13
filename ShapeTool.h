#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"
#include "MainWindow.h"

class ShapeTool : public ITool {
	ImageStack *imageStack;
	ImagePanel* imagePanel;
	MainWindow* mainWindow;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;
	ToolType toolType;

public:
	ShapeTool(ImageStack *is, ImagePanel* ip, MainWindow* mw, ToolType tt);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseUp(wxPoint pos);
	wxBitmap *getPreview();
	void drawDc(wxMemoryDC &dc, const wxRect &r);
};
