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

std::shared_ptr<LoadResult> Util::loadBitmap(const wxString &filename) {
	wxFFileInputStream fis(filename);
	{
		std::shared_ptr<wxPNGHandler> pngh(new wxPNGHandler());
		std::shared_ptr<wxBitmap> bmp(readBitmap(*pngh, fis));
		if (bmp) {
			return std::shared_ptr<LoadResult>(new LoadResult(filename, bmp, pngh));
		}
	}
	{
		std::shared_ptr<wxJPEGHandler> jpegh(new wxJPEGHandler());
		std::shared_ptr<wxBitmap> bmp(readBitmap(*jpegh, fis));
		if (bmp) {
			return std::shared_ptr<LoadResult>(new LoadResult(filename, bmp, jpegh));
		}
	}
	return std::shared_ptr<LoadResult>();
}

bool Util::saveBitmap(wxBitmap *bmp, const wxString &filename, wxImageHandler &imageHandler) {
	wxFFileOutputStream fos(filename);
	wxImage img(bmp->ConvertToImage());
	img.SetOption(wxIMAGE_OPTION_QUALITY, 90);
	return imageHandler.SaveFile(&img, fos);
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

 std::shared_ptr<wxImageHandler> Util::filenameToHandler(const wxString &filename) {
	wxString f = filename.Lower();
	if (f.EndsWith(".jpg") || f.EndsWith(".jpeg")) {
		return std::shared_ptr<wxImageHandler>(new wxJPEGHandler());
	}
	else if (f.EndsWith(".png")) {
		return std::shared_ptr<wxImageHandler>(new wxPNGHandler());
	}
	return std::shared_ptr<wxImageHandler>();
 }