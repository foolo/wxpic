#pragma once
#include <wx/bitmap.h>
#include <memory>

class LoadedFile {
public:
	std::shared_ptr<wxBitmap> bitmap;
	wxString filename;
	std::shared_ptr<wxImageHandler> imageHandler;
	LoadedFile(std::shared_ptr<wxBitmap> bitmap, wxString filename, std::shared_ptr<wxImageHandler> imageHandler);
};
