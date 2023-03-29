#pragma once

class IImageListener {
public:
	virtual void imageSizeChanged() = 0;
	virtual ~IImageListener() {}
};
