#include "Types.h"

ActiveFile::ActiveFile(wxString filename, std::shared_ptr<wxImageHandler> imageHandler) :
	filename(filename),
	imageHandler(imageHandler)
{
}

LoadResult::LoadResult(std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler) :
	bitmap(bitmap),
	imageHandler(imageHandler)
{
}
