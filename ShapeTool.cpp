#include "ShapeTool.h"
#include <wx/dcmemory.h>
#include <iostream>

ShapeTool::ShapeTool(IImageSource* imageSource) :
		imageSource(imageSource), startPos(wxDefaultCoord, wxDefaultCoord)
{
}

void ShapeTool::mouseDown(wxPoint pos) {
	startPos = pos;
}

void ShapeTool::mouseMoved(wxPoint pos) {
	if (startPos.IsFullySpecified()) {
		preview = std::unique_ptr<wxBitmap>(new wxBitmap(*imageSource->getImage()));
		wxMemoryDC dc;
		dc.SelectObject(*preview);
		dc.SetPen(wxPen(*wxRED));
		wxSize size(pos.x - startPos.x, pos.y - startPos.y);
		dc.DrawRectangle(startPos, size);
	}
}

void ShapeTool::mouseUp(wxPoint pos) {
	wxMemoryDC dc;
	dc.SelectObject(*imageSource->getImage());
	dc.SetPen(wxPen(*wxRED));
	preview = std::unique_ptr<wxBitmap>();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
}

wxBitmap* ShapeTool::getPreview() {
	return preview.get();
}
