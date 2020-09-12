#include "ShapeTool.h"
#include <wx/dcmemory.h>
#include <iostream>

ShapeTool::ShapeTool(ImageStack* imageSource, ImagePanel* imagePanel, MainWindow* mainWindow) :
		imageStack(imageSource),
		imagePanel(imagePanel),
		mainWindow(mainWindow),
		startPos(wxDefaultCoord, wxDefaultCoord)
{
}

void ShapeTool::mouseDown(wxPoint pos) {
	startPos = pos;
	mouseMoved(pos);
}

void ShapeTool::mouseMoved(wxPoint pos) {
	if (startPos.IsFullySpecified() == false) {
		return;
	}
	preview = std::shared_ptr<wxBitmap>(new wxBitmap(*imageStack->getImage()));
	wxMemoryDC dc;
	dc.SelectObject(*preview);
	dc.SetPen(wxPen(mainWindow->getPrimaryColor(), mainWindow->getBrushSize()));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	wxSize size(pos.x - startPos.x, pos.y - startPos.y);
	dc.DrawRectangle(startPos, size);
	imagePanel->Refresh();
}

void ShapeTool::mouseUp(wxPoint pos) {
	wxMemoryDC dc;
	dc.SelectObject(*imageStack->getImage());
	dc.SetPen(wxPen(mainWindow->getPrimaryColor()));
	imageStack->pushImage(preview);
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
	imagePanel->Refresh();
}

wxBitmap* ShapeTool::getPreview() {
	return preview.get();
}
