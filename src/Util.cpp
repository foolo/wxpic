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

LoadedFile *Util::loadBitmap(const wxString &filename) {
	wxFFileInputStream fis(filename);
	{
		std::shared_ptr<wxPNGHandler> pngh(new wxPNGHandler());
		std::shared_ptr<wxBitmap> bmp(readBitmap(*pngh, fis));
		if (bmp) {
			return new LoadedFile(bmp, filename, pngh);
		}
	}
	{
		std::shared_ptr<wxJPEGHandler> jpegh(new wxJPEGHandler());
		std::shared_ptr<wxBitmap> bmp(readBitmap(*jpegh, fis));
		if (bmp) {
			return new LoadedFile(bmp, filename, jpegh);
		}
	}
	return NULL;
}

void Util::saveBitmap(wxBitmap *bmp, const wxString &filename, wxImageHandler &imageHandler) {
	wxFFileOutputStream fos(filename);
	wxImage img(bmp->ConvertToImage());
	img.SetOption(wxIMAGE_OPTION_QUALITY, 90);
	imageHandler.SaveFile(&img, fos);
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
