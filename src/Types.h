#pragma once
#include <wx/bitmap.h>
#include <memory>

class ActiveFile {
public:
	wxString filename;
	std::shared_ptr<wxImageHandler> imageHandler;
	ActiveFile(wxString filename, std::shared_ptr<wxImageHandler> imageHandler);
};

class LoadResult {
public:
	std::shared_ptr<wxBitmap> bitmap;
	std::shared_ptr<wxImageHandler> imageHandler;
	LoadResult(std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler);
};
