#pragma once
#include "Types.h"
#include <wx/bitmap.h>
#include <wx/wfstream.h>
#include <vector>
#include <filesystem>

class Util {
public:
	static std::shared_ptr<LoadResult> loadBitmap(const wxString &filename);
	static void saveBitmap(wxBitmap *bmp, const wxString &filename, wxImageHandler &imageHandler);
	static int limit(int val, int min, int max);
	static std::shared_ptr<wxImageHandler> filenameToHandler(const wxString &filename);
	static wxPoint getUpperLeft(const wxPoint &p1, const wxPoint &p2);
	static wxPoint getLowerRight(const wxPoint &p1, const wxPoint &p2);
	static wxPoint limit(const wxPoint &p, const wxSize &size);
	static unsigned findIndex(int value, const std::vector<int> &sortedValues);
	static std::filesystem::path getConfigDir();
};
