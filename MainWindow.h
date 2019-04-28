#pragma once



#include "MainWindowLayout.h"

class MainWindow : public MainWindowLayout
{
public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(wxString filename);
private:

};
