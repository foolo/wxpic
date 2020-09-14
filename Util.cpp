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
