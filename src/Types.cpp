#include "Types.h"

ActiveFile::ActiveFile(wxString path, std::shared_ptr<wxImageHandler> imageHandler) :
	path(path),
	imageHandler(imageHandler)
{
}

LoadResult::LoadResult(std::shared_ptr<wxBitmap> bitmap, std::shared_ptr<wxImageHandler> imageHandler) :
	bitmap(bitmap),
	imageHandler(imageHandler)
{
}
