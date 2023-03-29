#pragma once
#include <wx/string.h>

class IStatusListener {
public:
	virtual void updatePositionStatus(const wxString& text) = 0;
	virtual void updateZoomStatus(double zoomScale) = 0;
	virtual void updateToolStatus(const wxString& text) = 0;
	virtual ~IStatusListener() {}
};