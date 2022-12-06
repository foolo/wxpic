#include "Types.h"

ActiveFile::ActiveFile(wxString path, std::shared_ptr<wxImageHandler> imageHandler) :
	path(path),
	imageHandler(imageHandler)
{
}

LoadResult::LoadResult(wxString path, std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler) :
	path(path),
	bitmap(bitmap),
	imageHandler(imageHandler)
{
}
