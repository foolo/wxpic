#pragma once
#include "ImageStack.h"
#include "ITool.h"
#include <memory>
#include <wx/wx.h>
#include <wx/sizer.h>

class ImagePanel : public wxWindow {
	bool pressedDown;
	static const int buttonWidth = 200;
	static const int buttonHeight = 50;

	ImageStack *imageStack;
	std::unique_ptr<ITool> tool;
	int zoomScrollLevel = 0;
	double zoomScale = 1.0;
	static constexpr const double zoomLevelMap[] = {1.0, 1.5, 2.0, 3.0, 4.0};

private:
	wxPoint mouseToImg(const wxPoint &mp);
	double zoomLevelToScale(int n);

public:
	ImagePanel(wxFrame* parent);

	void setImageSource(ImageStack *is);
	void setTool(ITool *t);

	void paintEvent(wxPaintEvent & evt);

	void render(wxDC& dc);

	void mouseDown(wxMouseEvent& event);
	void mouseMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
};

