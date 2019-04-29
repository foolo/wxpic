#pragma once
#include <wx/gdicmn.h>

class ITool {
public:
	virtual ~ITool() {};
	virtual void mouseDown(wxPoint pos) = 0;
	virtual void mouseUp(wxPoint pos) = 0;
};

class NullTool : public ITool {
public:
	void mouseDown(wxPoint pos) {};
	void mouseUp(wxPoint pos) {};
};
