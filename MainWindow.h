#pragma once

#include <memory>
#include "MainWindowLayout.h"
#include "UndoBuffer.h"

class MainWindow : public MainWindowLayout
{
	std::unique_ptr<UndoBuffer> undoBuffer;

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(wxString filename);

	void button_3_clicked(wxCommandEvent &event);
	DECLARE_EVENT_TABLE();
private:

};
