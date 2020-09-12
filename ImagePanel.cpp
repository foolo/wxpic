#include "ImagePanel.h"

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
    if (preview != NULL) {
    	dc.DrawBitmap(*preview, wxPoint(0,0));
    }
    else {
    	std::shared_ptr<wxBitmap> bmp(imageStack->getImage());
    	dc.DrawBitmap(*bmp.get(), wxPoint(0,0));
    }
}

void ImagePanel::mouseDown(wxMouseEvent& event) {
	tool->mouseDown(event.GetPosition());
    pressedDown = true;
}

void ImagePanel::mouseMoved(wxMouseEvent& event) {
	tool->mouseMoved(event.GetPosition());
}

void ImagePanel::mouseReleased(wxMouseEvent& event) {
	tool->mouseUp(event.GetPosition());
    pressedDown = false;
}
void ImagePanel::mouseLeftWindow(wxMouseEvent& event) {
    if (pressedDown) {
        pressedDown = false;
    }
}

// currently unused events
void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {
	std::cout << "key pressed " << event.GetKeyCode() << std::endl;
}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

