#pragma once
#include <wx/bitmap.h>
#include <memory>

class ActiveFile {
public:
	const wxString path;
	const std::shared_ptr<wxImageHandler> imageHandler;
	ActiveFile(wxString path, std::shared_ptr<wxImageHandler> imageHandler);
};

class LoadResult {
public:
	std::shared_ptr<wxBitmap> bitmap;
	std::shared_ptr<wxImageHandler> imageHandler;
	LoadResult(std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler);
};
