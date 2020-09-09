#include "ImagePanel.h"

void ImagePanel::setImageSource(IImageSource *is) {
	imageSource = is;
	tool = std::unique_ptr<ITool>(new NullTool());
}

void ImagePanel::setTool(ITool* t) {
	tool = std::unique_ptr<ITool>(t);
}

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
    EVT_MOTION(ImagePanel::mouseMoved)
    EVT_LEFT_DOWN(ImagePanel::mouseDown)
    EVT_LEFT_UP(ImagePanel::mouseReleased)
    EVT_RIGHT_DOWN(ImagePanel::rightClick)
    EVT_LEAVE_WINDOW(ImagePanel::mouseLeftWindow)
    EVT_KEY_DOWN(ImagePanel::keyPressed)
    EVT_KEY_UP(ImagePanel::keyReleased)
    EVT_MOUSEWHEEL(ImagePanel::mouseWheelMoved)

    // catch paint events
    EVT_PAINT(ImagePanel::paintEvent)
END_EVENT_TABLE()


ImagePanel::ImagePanel(wxFrame* parent) :
 wxWindow(parent, wxID_ANY), imageSource(NULL)
{
    SetMinSize( wxSize(buttonWidth, buttonHeight) );
    pressedDown = false;
    tool = std::unique_ptr<ITool>(new NullTool());
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC&  dc) {
    wxBitmap *preview = tool->getPreview();
    if (preview != NULL) {
    	dc.DrawBitmap(*preview, wxPoint(0,0));
    }
    else if (imageSource != NULL) {
    	std::shared_ptr<wxBitmap> bmp(imageSource->getImage());
    	dc.DrawBitmap(*bmp.get(), wxPoint(0,0));
    }
}

void ImagePanel::mouseDown(wxMouseEvent& event) {
	tool->mouseDown(event.GetPosition());
    pressedDown = true;
    paintNow();
}

void ImagePanel::mouseMoved(wxMouseEvent& event) {
	tool->mouseMoved(event.GetPosition());
	paintNow();
}

void ImagePanel::mouseReleased(wxMouseEvent& event) {
	tool->mouseUp(event.GetPosition());
    pressedDown = false;
    paintNow();
}
void ImagePanel::mouseLeftWindow(wxMouseEvent& event) {
    if (pressedDown) {
        pressedDown = false;
        paintNow();
    }
}

// currently unused events
void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

