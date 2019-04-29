#include <wx/dcmemory.h>
#include "ShapeTool.h"

void ShapeTool::mouseDown(wxPoint pos) {
	startPos = pos;
}

ShapeTool::ShapeTool(IImageSource* imageSource) :
		imageSource(imageSource)
{
}

void ShapeTool::mouseUp(wxPoint pos) {
	wxMemoryDC dc;
	dc.SelectObject(*imageSource->getImage());
	dc.SetPen(wxPen(*wxRED));
	dc.DrawRectangle(wxPoint(10,10), wxSize(50,50));
}
