#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"
#include "MainWindow.h"

class BlurTool : public ITool {
	ImageStack *imageStack;
	MainWindow* mainWindow;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;

public:
	BlurTool(ImageStack *is, MainWindow* mw);
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
