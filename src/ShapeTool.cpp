#include "ShapeTool.h"
#include <wx/dcmemory.h>
#include <iostream>

ShapeTool::ShapeTool(ImageStack* is, MainWindow* mw, ToolType tt) :
		imageStack(is),
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
}

void ShapeTool::mouseLeaving(wxPoint pos) {
}

void ShapeTool::mouseUp(wxPoint pos) {
	if (!preview) {
		return;
	}
	imageStack->pushImage(preview);
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
}

std::shared_ptr<wxBitmap> ShapeTool::getPreview() {
	return preview;
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

void drawArrow(wxMemoryDC &dc, const wxRect &r) {
	int width = std::max(10, dc.GetPen().GetWidth() * 3);
	wxPoint p0 = r.GetLeftTop();
	wxPoint p1 = r.GetRightBottom();
	double point_angle = 0.6;
	double angle = std::atan2(r.height, r.width);
	double dx_r = std::cos(angle - point_angle) * width;
	double dy_r = std::sin(angle - point_angle) * width;
	double dx_l = std::cos(angle + point_angle) * width;
	double dy_l = std::sin(angle + point_angle) * width;
	wxPoint pa_r = p1 - wxPoint(dx_r, dy_r);
	wxPoint pa_l = p1 - wxPoint(dx_l, dy_l);
	dc.DrawLine(p0, p1);
	dc.DrawLine(p1, pa_r);
	dc.DrawLine(p1, pa_l);
}

void ShapeTool::drawDc(wxMemoryDC &dc, const wxRect &r) {
	switch (toolType) {
	case ToolType::RECTANGLE: dc.DrawRectangle(r); break;
	case ToolType::ROUNDED_RECTANGLE: dc.DrawRoundedRectangle(normalize(r), getRoundedRadius(r)); break;
	case ToolType::ELLIPSE: dc.DrawEllipse(normalize(r)); break;
	case ToolType::LINE: dc.DrawLine(r.GetLeftTop(), r.GetBottomRight()); break;
	case ToolType::ARROW: drawArrow(dc, r); break;
	default: break;
	}
}

void ShapeTool::reset() {
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
}
