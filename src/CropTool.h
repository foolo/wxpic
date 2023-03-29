#pragma once
#include "ImageStack.h"
#include "ImagePanel.h"
#include "ITool.h"
#include "MainWindow.h"

class CropTool : public ITool {
	ImageStack *imageStack;
	MainWindow* mainWindow;
	wxPoint startPos;
	std::shared_ptr<wxBitmap> preview;
	IImageListener *imageListener;

public:
	CropTool(ImageStack *is, MainWindow* mw, IImageListener *il);
	void mouseDown(wxPoint pos);
	void mouseMoved(wxPoint pos);
	void mouseLeaving(wxPoint pos);
	void mouseUp(wxPoint pos);
	std::shared_ptr<wxBitmap> getPreview();
	bool busy();
	void resetPreview();
};
