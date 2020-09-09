#pragma once

#include "IImageSource.h"
#include <vector>
#include <memory>
#include <wx/bitmap.h>

class UndoBuffer : public IImageSource {

	std::vector<std::shared_ptr<wxBitmap> > buffer;
	std::shared_ptr<wxBitmap> activeBmp;

public:
	UndoBuffer(std::shared_ptr<wxBitmap> bmp);
	std::shared_ptr<wxBitmap> getImage();
};
