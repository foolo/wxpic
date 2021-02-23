#include "Util.h"

wxBitmap *readBitmap(wxImageHandler &ih, wxFFileInputStream &fis) {
	if (ih.CanRead(fis)) {
		wxImage img;
		if (ih.LoadFile(&img, fis)) {
			return new wxBitmap(img);
		}
	}
	return NULL;
}

wxBitmap *Util::loadBitmap(wxFFileInputStream &fis) {
	{
		wxPNGHandler pngh;
		wxBitmap *bmp = readBitmap(pngh, fis);
		if (bmp != NULL) {
			return bmp;
		}
	}
	{
		wxJPEGHandler jpegh;
		wxBitmap *bmp = readBitmap(jpegh, fis);
		if (bmp != NULL) {
			return bmp;
		}
	}
	return NULL;
}

int Util::limit(int val, int min, int max) {
	if (val < min) {
		return min;
	}
	if (val > max) {
		return max;
	}
	return val;
}
