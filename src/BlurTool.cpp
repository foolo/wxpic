#include "BlurTool.h"
#include "Util.h"
#include <wx/dcmemory.h>
#include <iostream>

BlurTool::BlurTool(ImageStack* is, MainWindow* mw) :
		imageStack(is),
		mainWindow(mw),
		startPos(wxDefaultCoord, wxDefaultCoord)
{
}

void BlurTool::mouseDown(wxPoint pos) {
	startPos = pos;
	mouseMoved(pos);
}

void BlurTool::mouseMoved(wxPoint pos) {
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
	mainWindow->updateToolStatus("Blur: " + std::to_string(size.GetX()) + ", " +  std::to_string(size.GetY()));
}

void BlurTool::mouseLeaving(wxPoint pos) {
}

void BlurTool::mouseUp(wxPoint pos) {
	imageStack->pushImage(preview);
	preview.reset();
	startPos = wxPoint(wxDefaultCoord, wxDefaultCoord);
	mainWindow->updateToolStatus("");
}

std::shared_ptr<wxBitmap> BlurTool::getPreview() {
	return preview;
}

void BlurTool::drawDc(wxMemoryDC &dc, const wxRect &r) {
	wxPoint p1(Util::limit(r.GetTopLeft(), dc.GetSize()));
	wxPoint p2(Util::limit(r.GetRightBottom(), dc.GetSize()));
	wxRect limitedRect(p1, p2);
	wxBitmap dcBmp = dc.GetAsBitmap();
	wxImage img = dcBmp.GetSubBitmap(wxRect(0, 0, dcBmp.GetWidth(), dcBmp.GetHeight())).ConvertToImage();
	wxImage blurredAreaImg = img.GetSubImage(limitedRect).Blur(mainWindow->getBrushSize());
	wxBitmap bmp = wxBitmap(blurredAreaImg);
	dc.DrawBitmap(bmp, limitedRect.GetTopLeft());
}

bool BlurTool::busy() {
	return startPos.IsFullySpecified();
}

void BlurTool::resetPreview() {
	preview.reset();
}
