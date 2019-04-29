#pragma once

#include <memory>
#include <wx/wx.h>
#include <wx/sizer.h>
#include "IImageSource.h"
#include "ITool.h"

class ImagePanel : public wxWindow
{

    bool pressedDown;
    wxString text;

    static const int buttonWidth = 200;
    static const int buttonHeight = 50;

    IImageSource *imageSource;
    std::unique_ptr<ITool> tool;

public:
    ImagePanel(wxFrame* parent, wxString text);

    void setImageSource(IImageSource *is);
    void setTool(ITool *t);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);

    DECLARE_EVENT_TABLE()
};

