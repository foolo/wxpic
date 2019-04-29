#pragma once

#include <memory>
#include <wx/image.h>

class IImageSource {
public:
	virtual ~IImageSource() {};
	virtual std::shared_ptr<wxBitmap> getImage() = 0;
};
