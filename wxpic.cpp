#include "MainWindow.h"
#include <vector>
#include <string>
#include <wx/wx.h>
#include <wx/image.h>

class MyApp: public wxApp {
public:
	bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
	std::vector<std::string> args;
	for (int i = 1; i < wxApp::argc; i++) {
		args.push_back(std::string(wxApp::argv[i]));
	}

	wxLog* logger = new wxLogStream(&std::cout);
	wxLog::SetActiveTarget(logger);

	wxInitAllImageHandlers();
	MainWindow* mainWindow0 = new MainWindow(NULL, wxID_ANY, wxEmptyString);
	SetTopWindow(mainWindow0);
	mainWindow0->Show();
	if (args.size() > 0) {
		mainWindow0->open(args.at(0));
	}
	return true;
}
