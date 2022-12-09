#include "CropTool.h"
#include "Util.h"
#include <wx/dcmemory.h>
#include <iostream>

CropTool::CropTool(ImageStack* is, MainWindow* mw) :
		imageStack(is),
		mainWindow(mw),
		startPos(wxDefaultCoord, wxDefaultCoord)
{
}

void CropTool::mouseDown(wxPoint pos) {
	startPos = pos;
	mouseMoved(pos);
}

void drawCropPreview(wxMemoryDC &dc, const wxPoint &p1, const wxPoint &p2) {
	static wxPen pen(wxColor(255, 255, 255, 128), 1);
	static wxBrush brush(wxColor(0,0,0, 85));
	wxSize size(std::max(p2.x - p1.x, 0), std::max(p2.y - p1.y, 0));
	wxBitmap bmp(size);
	wxMemoryDC tmpDc;
	tmpDc.SelectObject(bmp);
	tmpDc.Blit(wxPoint(0,0), size, &dc, p1);
	dc.SetBrush(brush);
	dc.DrawRectangle(wxRect(0,0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight()));
	dc.Blit(p1, size, &tmpDc, wxPoint(0,0));
	dc.SetPen(pen);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawLine(0, p1.y, dc.GetSize().GetWidth(), p1.y);
	dc.DrawLine(p1.x, 0, p1.x, dc.GetSize().GetHeight());
	dc.DrawLine(0, p2.y, dc.GetSize().GetWidth(), p2.y);
	dc.DrawLine(p2.x, 0, p2.x, dc.GetSize().GetHeight());
}

void CropTool::mouseMoved(wxPoint pos) {
	preview = std::shared_ptr<wxBitmap>(new wxBitmap(*imageStack->getImage()));
	wxMemoryDC dc;
	dc.SelectObject(*preview);
	if (startPos.IsFullySpecified() == false) {
		if (pos.x >= 0 && pos.y >= 0 && pos.x < dc.GetSize().GetWidth() && pos.y < dc.GetSize().GetHeight()) {
			wxPoint p2(dc.GetSize().GetWidth(), dc.GetSize().GetHeight());
			drawCropPreview(dc, pos, p2);
		}
	}
	else {
		wxPoint p1(Util::limit(Util::getUpperLeft(pos, startPos), dc.GetSize()));
		wxPoint p2(Util::limit(Util::getLowerRight(pos, startPos), dc.GetSize()));
		drawCropPreview(dc, p1, p2);
	}
}

void CropTool::mouseLeaving(wxPoint pos) {
	preview.reset();
}

void CropTool::mouseUp(wxPoint pos) {
	if (startPos.IsFullySpecified() == false) {
		return;
	}
	wxMemoryDC dc;
	dc.SelectObject(*imageStack->getImage());
	wxPoint p1(Util::limit(Util::getUpperLeft(pos, startPos), dc.GetSize()));
	wxPoint p2(Util::limit(Util::getLowerRight(pos, startPos), dc.GetSize()));
	wxSize size(p2.x - p1.x, p2.y - p1.y);
	if (size.x > 0 && size.y > 0) {
		std::shared_ptr<wxBitmap> bmp(new wxBitmap(size));
		wxMemoryDC tmpDc;
		tmpDc.SelectObject(*bmp);
		tmpDc.Blit(wxPoint(0,0), size, &dc, p1);
		imageStack->pushImage(bmp);
	}
	reset();
}

std::shared_ptr<wxBitmap> CropTool::getPreview() {
	return preview;
}

void CropTool::reset() {
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
}
