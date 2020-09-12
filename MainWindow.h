#pragma once

#include "MainWindowLayout.h"
#include <memory>
#include "ImageStack.h"

class MainWindow : public MainWindowLayout
{
	ImageStack imageStack;

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(wxString filename);

	void button_3_clicked(wxCommandEvent &event);
	void button_4_clicked(wxCommandEvent &event);
	void button_5_clicked(wxCommandEvent &event);
	void button_6_clicked(wxCommandEvent &event);
	void color_button_clicked(wxCommandEvent &event);
	void undo(wxCommandEvent &event);
};
