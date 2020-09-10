#include "MainWindow.h"
#include "ShapeTool.h"
#include <wx/wfstream.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title)
 : MainWindowLayout(parent, id, title)
{
	Bind(wxEVT_BUTTON, &MainWindow::button_3_clicked, this, button_3->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_4_clicked, this, button_4->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_5_clicked, this, button_5->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_6_clicked, this, button_6->GetId());
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
		imageStack = std::unique_ptr<ImageStack>(new ImageStack(bmp));
		imagePanel->setImageSource(imageStack.get());
		imagePanel->setTool(new ShapeTool(imageStack.get()));
	}
}

void MainWindow::button_3_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_3_clicked" << std::endl;
}

void MainWindow::button_4_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_4_clicked" << std::endl;
}

void MainWindow::button_5_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_5_clicked" << std::endl;
}

void MainWindow::button_6_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_6_clicked" << std::endl;
}
