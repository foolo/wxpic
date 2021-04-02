#include "ImagePanel.h"
#include "Util.h"
#include <iterator>

ImagePanel::ImagePanel(wxFrame* parent) :
 wxWindow(parent, wxID_ANY), imageStack(NULL)
{
	SetMinSize( wxSize(buttonWidth, buttonHeight) );
	tool = std::unique_ptr<ITool>(new NullTool());
	Bind(wxEVT_MOTION, &ImagePanel::mouseMoved, this);
	Bind(wxEVT_LEFT_DOWN, &ImagePanel::mouseLeftDown, this);
	Bind(wxEVT_MIDDLE_DOWN, &ImagePanel::mouseMiddleDown, this);
	Bind(wxEVT_MIDDLE_UP, &ImagePanel::mouseMiddleReleased, this);
	Bind(wxEVT_LEFT_UP, &ImagePanel::mouseLeftReleased, this);
	Bind(wxEVT_RIGHT_DOWN, &ImagePanel::rightClick, this);
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
	dc.SetDeviceOrigin(imagePanPos.x, imagePanPos.y);
	if (preview != NULL) {
		dc.DrawBitmap(*preview, wxPoint(0,0));
	}
	else {
		std::shared_ptr<wxBitmap> bmp(imageStack->getImage());
		dc.DrawBitmap(*bmp.get(), wxPoint(0,0));
	}
}

wxPoint ImagePanel::mouseToImg(const wxPoint &mp) {
	wxPoint dm = mp - imagePanPos;
	return wxPoint(dm.x / zoomScale, dm.y / zoomScale);
}

wxPoint ImagePanel::imgToMouse(const wxPoint &ic) {
	return ic * zoomScale + imagePanPos;
}

void ImagePanel::mouseLeftDown(wxMouseEvent& event) {
	if (inputState == InputState::IDLE) {
		tool->mouseDown(mouseToImg(event.GetPosition()));
		inputState = InputState::LEFT_DOWN;
	}
}

void ImagePanel::mouseMiddleDown(wxMouseEvent& event) {
	if (inputState == InputState::IDLE) {
		panGrabPosInImage = event.GetPosition() - imagePanPos;
		inputState = InputState::MIDDLE_DOWN;
	}
}

void ImagePanel::mouseMiddleReleased(wxMouseEvent& event) {
	if (inputState == InputState::MIDDLE_DOWN) {
		inputState = InputState::IDLE;
	}
}

void ImagePanel::mouseMoved(wxMouseEvent& event) {
	if (inputState == InputState::LEFT_DOWN) {
		tool->mouseMoved(mouseToImg(event.GetPosition()));
	}
	else if (inputState == InputState::MIDDLE_DOWN) {
		imagePanPos = event.GetPosition() - panGrabPosInImage;
		Refresh();
	}
}

void ImagePanel::mouseLeftReleased(wxMouseEvent& event) {
	if (inputState == InputState::LEFT_DOWN) {
		tool->mouseUp(mouseToImg(event.GetPosition()));
		inputState = InputState::IDLE;
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
		wxPoint zoomPointInImage = mouseToImg(event.GetPosition());

		zoomScrollLevel += event.GetWheelRotation();
		const int maxZoomLevel = std::size(zoomLevelMap) - 1;
		int zoomLevel = Util::limit(zoomScrollLevel / event.GetWheelDelta(), -maxZoomLevel, maxZoomLevel);
		zoomScale = zoomLevelToScale(zoomLevel);

		wxPoint newAnchorPos = imgToMouse(zoomPointInImage);
		wxPoint dm = newAnchorPos - event.GetPosition();
		imagePanPos -= dm;

		Refresh();
	}
}

// currently unused events
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {
	std::cout << "key pressed " << event.GetKeyCode() << std::endl;
}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

