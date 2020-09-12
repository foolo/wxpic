#include "ShapeTool.h"
#include <wx/dcmemory.h>
#include <iostream>

ShapeTool::ShapeTool(ImageStack* imageSource, ImagePanel* imagePanel) :
		imageStack(imageSource), imagePanel(imagePanel), startPos(wxDefaultCoord, wxDefaultCoord)
{
}

void ShapeTool::mouseDown(wxPoint pos) {
	startPos = pos;
	mouseMoved(pos);
}

void ShapeTool::mouseMoved(wxPoint pos) {
	if (startPos.IsFullySpecified()) {
		preview = std::shared_ptr<wxBitmap>(new wxBitmap(*imageStack->getImage()));
		wxMemoryDC dc;
		dc.SelectObject(*preview);
		dc.SetPen(wxPen(*wxRED));
		wxSize size(pos.x - startPos.x, pos.y - startPos.y);
		dc.DrawRectangle(startPos, size);
		imagePanel->Refresh();
	}
}

void ShapeTool::mouseUp(wxPoint pos) {
	wxMemoryDC dc;
	dc.SelectObject(*imageStack->getImage());
	dc.SetPen(wxPen(*wxRED));
	imageStack->pushImage(preview);
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
	imagePanel->Refresh();
}

wxBitmap* ShapeTool::getPreview() {
	return preview.get();
}
