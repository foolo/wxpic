#include "MainWindow.h"

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title) : MainWindowLayout(parent, id, title)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::open(wxString filename)
{
	std::cout << "open " << filename << std::endl;
}
