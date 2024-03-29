#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"
#include "MainWindow.h"

enum class ToolType {
	RECTANGLE,
	RECTANGLE_FILLED,
	ROUNDED_RECTANGLE,
	ELLIPSE,
	LINE,
	ARROW
};

class ShapeTool : public ITool {
	ImageStack *imageStack;
	MainWindow* mainWindow;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;
	ToolType toolType;

public:
	ShapeTool(ImageStack *is, MainWindow* mw, ToolType tt);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseLeaving(wxPoint pos);
	void mouseUp(wxPoint pos);
	std::shared_ptr<wxBitmap> getPreview();
	void drawDc(wxMemoryDC &dc, const wxRect &r);
	bool busy();
	void resetPreview();

private:
	wxString getToolName();
};
