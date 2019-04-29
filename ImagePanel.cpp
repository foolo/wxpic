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


ImagePanel::ImagePanel(wxFrame* parent, wxString text) :
 wxWindow(parent, wxID_ANY), imageSource(NULL)
{
    SetMinSize( wxSize(buttonWidth, buttonHeight) );
    this->text = text;
    pressedDown = false;
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void ImagePanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void ImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void ImagePanel::render(wxDC&  dc)
{
    if (pressedDown)
        dc.SetBrush( *wxRED_BRUSH );
    else
        dc.SetBrush( *wxGREY_BRUSH );

    dc.DrawRectangle( 0, 0, buttonWidth, buttonHeight );
    dc.DrawText( text, 20, 15 );
    if (imageSource != NULL) {
    	std::shared_ptr<wxBitmap> bmp(imageSource->getImage());
    	dc.DrawBitmap(*bmp.get(), wxPoint(0,0));
    }
}

void ImagePanel::mouseDown(wxMouseEvent& event)
{
	tool->mouseDown(event.GetPosition());
    pressedDown = true;
    paintNow();
}
void ImagePanel::mouseReleased(wxMouseEvent& event)
{
	tool->mouseUp(event.GetPosition());
    pressedDown = false;
    paintNow();

    wxMessageBox( wxT("You pressed a custom button") );
}
void ImagePanel::mouseLeftWindow(wxMouseEvent& event)
{
    if (pressedDown)
    {
        pressedDown = false;
        paintNow();
    }
}

// currently unused events
void ImagePanel::mouseMoved(wxMouseEvent& event) {}
void ImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
void ImagePanel::rightClick(wxMouseEvent& event) {}
void ImagePanel::keyPressed(wxKeyEvent& event) {}
void ImagePanel::keyReleased(wxKeyEvent& event) {}

