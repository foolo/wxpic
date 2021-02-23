#include "ImagePanel.h"
#include "Util.h"
#include <iterator>

ImagePanel::ImagePanel(wxFrame* parent) :
 wxWindow(parent, wxID_ANY), imageStack(NULL)
{
	SetMinSize( wxSize(buttonWidth, buttonHeight) );
	pressedDown = false;
	tool = std::unique_ptr<ITool>(new NullTool());
	Bind(wxEVT_MOTION, &ImagePanel::mouseMoved, this);
	Bind(wxEVT_LEFT_DOWN, &ImagePanel::mouseDown, this);
	Bind(wxEVT_LEFT_UP, &ImagePanel::mouseReleased, this);
	Bind(wxEVT_RIGHT_DOWN, &ImagePanel::rightClick, this);
	Bind(wxEVT_LEAVE_WINDOW, &ImagePanel::mouseLeftWindow, this);
	Bind(wxEVT_KEY_DOWN, &ImagePanel::keyPressed, this);
	Bind(wxEVT_KEY_UP, &ImagePanel::keyReleased, this);
	Bind(wxEVT_MOUSEWHEEL, &ImagePanel::mouseWheelMoved, this);
	Bind(wxEVT_PAINT, &ImagePanel::paintEvent, this);
}

void ImagePanel::setImageSource(ImageStack *is) {
	imageStack = is;
}

void ImagePanel::setTool(ITool* t) {
	tool = std::unique_ptr<ITool>(t);
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
	wxPaintDC dc(this);
	render(dc);
}

void ImagePanel::render(wxDC&  dc) {
	wxBitmap *preview = tool->getPreview();
	dc.SetUserScale(zoomScale, zoomScale);
	if (preview != NULL) {
		dc.DrawBitmap(*preview, wxPoint(0,0));
	}
	else {
		std::shared_ptr<wxBitmap> bmp(imageStack->getImage());
		dc.DrawBitmap(*bmp.get(), wxPoint(0,0));
	}
}

wxPoint ImagePanel::mouseToImg(const wxPoint &mp) {
	return wxPoint(mp.x / zoomScale, mp.y / zoomScale);
}

void ImagePanel::mouseDown(wxMouseEvent& event) {
	tool->mouseDown(mouseToImg(event.GetPosition()));
	pressedDown = true;
}

void ImagePanel::mouseMoved(wxMouseEvent& event) {
	tool->mouseMoved(mouseToImg(event.GetPosition()));
}

void ImagePanel::mouseReleased(wxMouseEvent& event) {
	tool->mouseUp(mouseToImg(event.GetPosition()));
	pressedDown = false;
}
void ImagePanel::mouseLeftWindow(wxMouseEvent& event) {
	if (pressedDown) {
		pressedDown = false;
	}
}

double ImagePanel::zoomLevelToScale(int n) {
	unsigned i = std::abs(n);
	if (i >= std::size(zoomLevelMap)) {
		return 1.0;
	}
	if (n < 0) {
		return 1.0 / zoomLevelMap[i];
	}
	else {
		return zoomLevelMap[i];
	}
}

void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {
	if (event.GetModifiers() & wxMOD_CONTROL) {
		zoomScrollLevel += event.GetWheelRotation();
		const int maxZoomLevel = std::size(zoomLevelMap) - 1;
		int zoomLevel = Util::limit(zoomScrollLevel / event.GetWheelDelta(), -maxZoomLevel, maxZoomLevel);
		zoomScale = zoomLevelToScale(zoomLevel);
		Refresh();
	}
}

// currently unused events
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {
	std::cout << "key pressed " << event.GetKeyCode() << std::endl;
}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

