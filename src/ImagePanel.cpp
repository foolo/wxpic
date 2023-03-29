#include "ImagePanel.h"
#include "Util.h"
#include <iterator>

ImagePanel::ImagePanel(wxScrolledWindow* parent) :
 wxWindow(parent, wxID_ANY), imageStack(NULL), parentWindow(parent)
{
	SetMinSize( wxSize(buttonWidth, buttonHeight) );
	tool = std::unique_ptr<ITool>(new NullTool());
	Bind(wxEVT_MOTION, &ImagePanel::mouseMoved, this);
	Bind(wxEVT_LEAVE_WINDOW, &ImagePanel::mouseLeaving, this);
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
	Refresh();
}

void ImagePanel::setStatusListener(IStatusListener* sl) {
	statusListener = sl;
	statusListener->updateZoomStatus(zoomScale);
}

void ImagePanel::undo() {
	if (!tool->busy()) {
		imageStack->undo();
		tool->resetPreview();
	}
	Refresh();
}

void ImagePanel::redo() {
	if (!tool->busy()) {
		imageStack->redo();
		tool->resetPreview();
	}
	Refresh();
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
	wxPaintDC dc(this);
	render(dc);
}

std::shared_ptr<wxBitmap> ImagePanel::getVisibleBitmap() {
	std::shared_ptr<wxBitmap> preview(tool->getPreview());
	if (preview) {
		return preview;
	}
	else {
		return imageStack->getImage();
	}
}

void ImagePanel::render(wxDC&  dc) {
	std::shared_ptr<wxBitmap> bmp = getVisibleBitmap();
	dc.SetUserScale(zoomScale, zoomScale);
	dc.DrawBitmap(*bmp, wxPoint(0,0));
}

wxPoint ImagePanel::mouseToImg(const wxPoint &mp) {
	return wxPoint(mp.x / zoomScale, mp.y / zoomScale);
}

wxPoint ImagePanel::imgToMouse(const wxPoint &ic) {
	return ic * zoomScale;
}

void ImagePanel::mouseLeftDown(wxMouseEvent& event) {
	if (inputState == InputState::IDLE) {
		tool->mouseDown(mouseToImg(event.GetPosition()));
		inputState = InputState::LEFT_DOWN;
		Refresh();
	}
}

void ImagePanel::mouseMiddleDown(wxMouseEvent& event) {
	if (inputState == InputState::IDLE) {
		panGrabPosInImage = event.GetPosition();
		inputState = InputState::MIDDLE_DOWN;
	}
}

void ImagePanel::mouseMiddleReleased(wxMouseEvent& event) {
	if (inputState == InputState::MIDDLE_DOWN) {
		inputState = InputState::IDLE;
	}
}

void ImagePanel::mouseMoved(wxMouseEvent& event) {
	tool->mouseMoved(mouseToImg(event.GetPosition()));
	if (inputState == InputState::LEFT_DOWN) {
	}
	else if (inputState == InputState::MIDDLE_DOWN) {
		wxPoint dm = event.GetPosition() - panGrabPosInImage;
		wxPoint currentScrollPos = wxPoint(parentWindow->GetScrollPos(wxHORIZONTAL), parentWindow->GetScrollPos(wxVERTICAL));
		wxPoint newScrollPos = currentScrollPos - dm;
		wxSize ds = GetSize() - parentWindow->GetSize();
		parentWindow->Scroll(std::min(ds.x, newScrollPos.x), std::min(ds.y, newScrollPos.y));
	}
	if (statusListener) {
		statusListener->updatePositionStatus(std::to_string(event.GetX()) + ", " + std::to_string(event.GetY()));
	}
	Refresh();
}

void ImagePanel::mouseLeaving(wxMouseEvent& event) {
	tool->mouseLeaving(event.GetPosition());
	Refresh();
}

void ImagePanel::mouseLeftReleased(wxMouseEvent& event) {
	if (inputState == InputState::LEFT_DOWN) {
		tool->mouseUp(mouseToImg(event.GetPosition()));
		inputState = InputState::IDLE;
		Refresh();
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

void ImagePanel::adjustImagePos() {
	int imgWidth = getVisibleBitmap()->GetWidth() * zoomScale;
	int imgHeight = getVisibleBitmap()->GetHeight() * zoomScale;
	const int scrollbarPadding = 5;
	int scrollbarHeight = wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y);
	int scrollbarWidth = wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
	SetMinSize(wxSize(imgWidth + scrollbarWidth + scrollbarPadding, imgHeight + scrollbarHeight + scrollbarPadding));
	parentWindow->FitInside();
}

void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {
	if (event.GetModifiers() & wxMOD_CONTROL) {
		wxPoint zoomPointInImage = mouseToImg(event.GetPosition());
		zoomScrollLevel += event.GetWheelRotation();
		const int maxZoomLevel = std::size(zoomLevelMap) - 1;
		int newZoomLevel = Util::limit(zoomScrollLevel / event.GetWheelDelta(), -maxZoomLevel, maxZoomLevel);
		zoomScrollLevel = newZoomLevel * event.GetWheelDelta();
		if (newZoomLevel == zoomLevel) {
			return;
		}
		zoomLevel = newZoomLevel;
		zoomScale = zoomLevelToScale(zoomLevel);
		if (statusListener) {
			statusListener->updateZoomStatus(zoomScale);
		}

		wxPoint currentScrollPos = wxPoint(parentWindow->GetScrollPos(wxHORIZONTAL), parentWindow->GetScrollPos(wxVERTICAL));
		wxPoint eventRelPos = event.GetPosition() - currentScrollPos ;
		wxPoint newZoomPoint = imgToMouse(zoomPointInImage);
		wxPoint scrollPos = newZoomPoint - eventRelPos;
		adjustImagePos();

		wxSize ds = GetSize() - parentWindow->GetSize();
		parentWindow->Scroll(std::min(ds.x, scrollPos.x), std::min(ds.y, scrollPos.y));
		Refresh();
	}
}

// currently unused events
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {
	std::cout << "key pressed " << event.GetKeyCode() << std::endl;
}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

void ImagePanel::windowResized(wxSizeEvent& event) {
	adjustImagePos();
}
