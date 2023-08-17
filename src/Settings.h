#pragma once
#include <wx/colour.h>

class Settings {

public:
	static wxColor getPrimaryColor();
	static void setPrimaryColor(const wxColor &c);
};
