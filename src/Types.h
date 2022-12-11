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
	wxString path;
	std::shared_ptr<wxBitmap> bitmap;
	std::shared_ptr<wxImageHandler> imageHandler;
	LoadResult(wxString path, std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler);
};

class IOException : public std::exception {
private:
    std::string message;

public:
    IOException(const std::string message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
