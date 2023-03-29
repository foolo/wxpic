#pragma once
#include "ImageStack.h"
#include "ITool.h"
#include <memory>
#include <wx/wx.h>
#include <wx/sizer.h>

enum class InputState {IDLE, LEFT_DOWN, MIDDLE_DOWN};

class IStatusListener {
public:
	virtual void updatePositionStatus(const wxString& text) = 0;
	virtual void updateZoomStatus(double zoomScale) = 0;
	virtual ~IStatusListener() {}
};

class ImagePanel : public wxWindow {
	static const int buttonWidth = 200;
	static const int buttonHeight = 50;

	ImageStack *imageStack;
	std::unique_ptr<ITool> tool;
	int zoomScrollLevel = 0;
	double zoomScale = 1.0;
	int zoomLevel = 0;
	static constexpr const double zoomLevelMap[] = {1.0, 1.5, 2.0, 3.0, 4.0};
	wxPoint panGrabPosInImage;
	InputState inputState = InputState::IDLE;
	wxScrolledWindow* parentWindow;
	IStatusListener *statusListener = NULL;

private:
	wxPoint mouseToImg(const wxPoint &mp);
	wxPoint imgToMouse(const wxPoint &mp);
	double zoomLevelToScale(int n);
	std::shared_ptr<wxBitmap> getVisibleBitmap();

public:
	ImagePanel(wxScrolledWindow* parent);

	void setImageSource(ImageStack *is);
	void setTool(ITool *t);
	void setStatusListener(IStatusListener *sl);
	void undo();
	void redo();

	void paintEvent(wxPaintEvent & evt);

	void render(wxDC& dc);
	void adjustImagePos();

	void mouseLeftDown(wxMouseEvent& event);
	void mouseMiddleDown(wxMouseEvent& event);
	void mouseMiddleReleased(wxMouseEvent& event);
	void mouseMoved(wxMouseEvent& event);
	void mouseLeaving(wxMouseEvent& event);
	void mouseLeftReleased(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	void windowResized(wxSizeEvent& event);
};

