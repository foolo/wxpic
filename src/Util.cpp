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

void Util::saveBitmap(wxBitmap *bmp, const wxString &filename, wxImageHandler &imageHandler) {
	wxFFileOutputStream fos(filename);
	wxImage img(bmp->ConvertToImage());
	img.SetOption(wxIMAGE_OPTION_QUALITY, 90);
	if (imageHandler.SaveFile(&img, fos) == false) {
		throw IOException("");
	}
	wxStreamError err = fos.GetLastError();
	switch(err) {
		case wxSTREAM_NO_ERROR: return;
		case wxSTREAM_EOF: throw IOException("End of file");
		case wxSTREAM_WRITE_ERROR: throw IOException("Could not write file");
		case wxSTREAM_READ_ERROR: throw IOException("Could not read file");
		default: throw IOException("Unknown error code: " + std::to_string(err));
	}
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

wxPoint Util::getUpperLeft(const wxPoint &p1, const wxPoint &p2) {
	return wxPoint(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
}

wxPoint Util::getLowerRight(const wxPoint &p1, const wxPoint &p2) {
	return wxPoint(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}

wxPoint Util::limit(const wxPoint &p, const wxSize &size) {
	return wxPoint(std::min(std::max(p.x, 0), size.x), std::min(std::max(p.y, 0), size.y));
}
