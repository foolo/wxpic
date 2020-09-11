#include "MainWindow.h"
#include "ShapeTool.h"
#include <wx/wfstream.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title)
 : MainWindowLayout(parent, id, title)
{
	imagePanel->setImageSource(&imageStack);
	Bind(wxEVT_BUTTON, &MainWindow::button_3_clicked, this, button_3->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_4_clicked, this, button_4->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_5_clicked, this, button_5->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_6_clicked, this, button_6->GetId());
	Bind(wxEVT_MENU, &MainWindow::undo, this, wxID_UNDO);

	const int ENTRIES_CNT = 1;
	wxAcceleratorEntry entries[ENTRIES_CNT];
	entries[0].Set(wxACCEL_CTRL, (int) 'Z', wxID_UNDO);
	wxAcceleratorTable accel(ENTRIES_CNT, entries);
	SetAcceleratorTable(accel);
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
		imageStack.clear();
		imageStack.pushImage(bmp);
		imagePanel->setTool(new ShapeTool(&imageStack));
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

void MainWindow::undo(wxCommandEvent &event) {
	event.Skip();
	std::cout << "undo" << std::endl;
}
