#pragma once

#include "MainWindowLayout.h"
#include <memory>
#include "ImageStack.h"

class MainWindow : public MainWindowLayout
{
	std::unique_ptr<ImageStack> imageStack;

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(wxString filename);

	void button_3_clicked(wxCommandEvent &event);
	DECLARE_EVENT_TABLE();
private:

};
