#include "ColorPickerTool.h"
#include <wx/dcmemory.h>

ColorPickerTool::ColorPickerTool(ImageStack* is, MainWindow* mw) :
		imageStack(is),
		mainWindow(mw),
		mouseDownState(false)
{
}

void ColorPickerTool::mouseDown(wxPoint pos) {
	mouseDownState = true;
	mouseMoved(pos);
}

void ColorPickerTool::mouseMoved(wxPoint pos) {
	if (mouseDownState) {
		wxMemoryDC dc;
		dc.SelectObject(*imageStack->getImage());
		wxColour color;
		if (dc.GetPixel(pos, &color)) {
			mainWindow->setPrimaryColor(color);
		}
	}
}

void ColorPickerTool::mouseLeaving(wxPoint pos) {
}

void ColorPickerTool::mouseUp(wxPoint pos) {
	mouseDownState = false;
}

std::shared_ptr<wxBitmap> ColorPickerTool::getPreview() {
	return NULL;
}

bool ColorPickerTool::busy() {
	return false;
}

void ColorPickerTool::resetPreview() {
}
