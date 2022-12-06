#pragma once
#include "Types.h"
#include <wx/bitmap.h>
#include <wx/wfstream.h>

class Util {
public:
	static std::shared_ptr<LoadResult> loadBitmap(const wxString &filename);
	static void saveBitmap(wxBitmap *bmp, const wxString &filename, wxImageHandler &imageHandler);
	static int limit(int val, int min, int max);
};
