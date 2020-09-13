#include "ShapeTool.h"
#include <wx/dcmemory.h>
#include <iostream>

ShapeTool::ShapeTool(ImageStack* is, ImagePanel* ip, MainWindow* mw, ToolType tt) :
		imageStack(is),
		imagePanel(ip),
		mainWindow(mw),
		startPos(wxDefaultCoord, wxDefaultCoord),
		toolType(tt)
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
	drawDc(dc, wxRect(startPos, size));
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

wxRect normalize(wxRect r) {
	wxRect res(r);
	if (res.width < 0) {
		res.width = -res.width;
		res.x -= res.width;
	}
	if (res.height < 0) {
		res.height = -res.height;
		res.y -= res.height;
	}
	return res;
}

double getRoundedRadius(const wxRect &r) {
	const int ROUNDED_RECTANGLE_RADIUS = 10;
	int maxRadius = std::min(std::abs(r.width), std::abs(r.height)) / 2;
	return std::min(maxRadius, ROUNDED_RECTANGLE_RADIUS);
}

void ShapeTool::drawDc(wxMemoryDC &dc, const wxRect &r) {
	switch (toolType) {
	case ToolType::RECTANGLE: dc.DrawRectangle(r); break;
	case ToolType::ROUNDED_RECTANGLE: dc.DrawRoundedRectangle(normalize(r), getRoundedRadius(r)); break;
	case ToolType::ELLIPSE: dc.DrawEllipse(normalize(r)); break;
	case ToolType::LINE: dc.DrawLine(r.GetLeftTop(), r.GetBottomRight()); break;
	default: break;
	}
}
