#include "MainWindow.h"
#include "ShapeTool.h"
#include <wx/wfstream.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title)
 : MainWindowLayout(parent, id, title)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::open(wxString filename)
{
	wxImage img;
	wxFFileInputStream fis(filename);
	wxPNGHandler pngHandler;
	if (pngHandler.LoadFile(&img, fis)) {
		std::shared_ptr<wxBitmap> bmp(new wxBitmap(img));
		undoBuffer = std::unique_ptr<UndoBuffer>(new UndoBuffer(bmp));
		imagePanel->setImageSource(undoBuffer.get());
		imagePanel->setTool(new ShapeTool(undoBuffer.get()));
	}
}

void MainWindow::button_3_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "test1" << std::endl;
}


BEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(wxID_ANY, MainWindow::button_3_clicked)
END_EVENT_TABLE();
