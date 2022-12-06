#include "MainWindow.h"
#include "Util.h"
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

	std::shared_ptr<LoadResult> loadResult;
	if (args.size() > 0) {
		wxString filename(args.at(0));
		loadResult = Util::loadBitmap(filename);
		if (!loadResult) {
			wxMessageBox("Could not load file\n" + filename, "wxpic loading error", wxICON_ERROR);
			return false;
		}
	}

	MainWindow* mainWindow0 = new MainWindow(NULL, wxID_ANY, wxEmptyString);
	SetTopWindow(mainWindow0);
	mainWindow0->Show();
	if (loadResult) {
		mainWindow0->open(loadResult);
	}
	else {
		mainWindow0->newFile();
	}
	return true;
}
