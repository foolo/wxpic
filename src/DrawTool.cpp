#include "DrawTool.h"
#include <wx/dcmemory.h>
#include <iostream>

DrawTool::DrawTool(ImageStack* is, ImagePanel* ip, MainWindow* mw) :
		imageStack(is),
		imagePanel(ip),
		mainWindow(mw)
{
}

void DrawTool::mouseDown(wxPoint pos) {
	preview = std::shared_ptr<wxBitmap>(new wxBitmap(*imageStack->getImage()));
	lastMousePos = pos;
	mouseMoved(pos);
}

void DrawTool::mouseMoved(wxPoint pos) {
	if (!preview) {
		return;
	}
	wxMemoryDC dc;
	dc.SelectObject(*preview);
	dc.SetPen(wxPen(mainWindow->getPrimaryColor(), mainWindow->getBrushSize()));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawLine(lastMousePos, pos);
	lastMousePos = pos;
	imagePanel->Refresh();
}

void DrawTool::mouseLeaving(wxPoint pos) {
}

void DrawTool::mouseUp(wxPoint pos) {
	if (!preview) {
		return;
	}
	wxMemoryDC dc;
	dc.SelectObject(*imageStack->getImage());
	dc.SetPen(wxPen(mainWindow->getPrimaryColor()));
	imageStack->pushImage(preview);
	preview.reset();
	imagePanel->Refresh();
}

std::shared_ptr<wxBitmap> DrawTool::getPreview() {
	return preview;
}

void DrawTool::reset() {
	preview.reset();
}
