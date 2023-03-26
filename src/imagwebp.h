// based on https://github.com/hoehermann/wxWEBPHandler

#pragma once

#include <wx/image.h>

class wxWEBPHandler : public wxImageHandler {
public:
	inline wxWEBPHandler() {
		m_name = wxT("WebP file");
		m_extension = wxT("webp");
		m_type = wxBITMAP_TYPE_ANY; // no WEBP type constant available
		m_mime = wxT("image/webp");
	}

	virtual bool LoadFile(wxImage *image, wxInputStream& stream, bool verbose=true, int index=-1) override;
	virtual bool SaveFile(wxImage *image, wxOutputStream& stream, bool verbose=true) override;

protected:
	virtual bool DoCanRead(wxInputStream& stream) override;

private:
	wxDECLARE_DYNAMIC_CLASS(wxWEBPHandler);
};

