#pragma once
#include <wx/bitmap.h>
#include <wx/wfstream.h>

class Util {
public:
	static wxBitmap *loadBitmap(wxFFileInputStream &fis);
};