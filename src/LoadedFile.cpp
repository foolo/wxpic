#include "LoadedFile.h"

LoadedFile::LoadedFile(std::shared_ptr<wxBitmap> bitmap, wxString filename, std::shared_ptr<wxImageHandler> imageHandler) :
	bitmap(bitmap),
	filename(filename),
	imageHandler(imageHandler)
{
}
