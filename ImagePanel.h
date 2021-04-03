#pragma once
#include "ImageStack.h"
#include "ITool.h"
#include <memory>
#include <wx/wx.h>
#include <wx/sizer.h>

enum class InputState {IDLE, LEFT_DOWN, MIDDLE_DOWN};

class ImagePanel : public wxWindow {
	static const int buttonWidth = 200;
	static const int buttonHeight = 50;

	ImageStack *imageStack;
	std::unique_ptr<ITool> tool;
	int zoomScrollLevel = 0;
	double zoomScale = 1.0;
	static constexpr const double zoomLevelMap[] = {1.0, 1.5, 2.0, 3.0, 4.0};
	wxPoint imagePanPos;
	wxPoint panGrabPosInImage;
	InputState inputState = InputState::IDLE;

private:
	wxPoint mouseToImg(const wxPoint &mp);
	wxPoint imgToMouse(const wxPoint &mp);
	double zoomLevelToScale(int n);
	void adjustImagePos();
	std::shared_ptr<wxBitmap> getVisibleBitmap();

public:
	ImagePanel(wxFrame* parent);

	void setImageSource(ImageStack *is);
	void setTool(ITool *t);

	void paintEvent(wxPaintEvent & evt);

	void render(wxDC& dc);

	void mouseLeftDown(wxMouseEvent& event);
	void mouseMiddleDown(wxMouseEvent& event);
	void mouseMiddleReleased(wxMouseEvent& event);
	void mouseMoved(wxMouseEvent& event);
	void mouseLeftReleased(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
};

