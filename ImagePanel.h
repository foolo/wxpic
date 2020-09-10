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

public:
    ImagePanel(wxFrame* parent);

    void setImageSource(ImageStack *is);
    void setTool(ITool *t);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    void mouseDown(wxMouseEvent& event);
    void mouseMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
};

