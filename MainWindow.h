#pragma once

#include "MainWindowLayout.h"
#include "ImageStack.h"
#include <memory>
#include <vector>

class MainWindow : public MainWindowLayout
{
	ImageStack imageStack;
    const std::vector<int> brush_sizes{1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18};
    enum {
        RECTANGLE_ID,
        TOOL_ID_MAX,
    };
    std::vector<wxBitmap> icons;

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(wxString filename);

	void button_3_clicked(wxCommandEvent &event);
	void button_4_clicked(wxCommandEvent &event);
	void button_5_clicked(wxCommandEvent &event);
	void button_6_clicked(wxCommandEvent &event);
	void rectangle_tool_selected(wxCommandEvent &event);
	void color_button_clicked(wxCommandEvent &event);
	void undo(wxCommandEvent &event);
	wxColor getPrimaryColor();
	int getBrushSize();
	void createToolIcons();
};
