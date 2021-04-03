#pragma once
#include "MainWindowLayout.h"
#include "ImageStack.h"
#include <memory>
#include <vector>

enum class ToolType { RECTANGLE, ROUNDED_RECTANGLE, ELLIPSE, LINE, ARROW };

class IconId {
public:
	enum { RECTANGLE, ROUNDED_RECTANGLE, ELLIPSE, LINE, ARROW, DRAW, MAX };
};

class MainWindow : public MainWindowLayout {
	ImageStack imageStack;
	const std::vector<int> brush_sizes{1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18};
	std::vector<wxBitmap> icons;
	wxString loadedFilename;

private:
	wxBitmap *loadBitmap(const wxString &filename);
	void updateTitle();

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void open(const wxString &filename);

	void button_3_clicked(wxCommandEvent &event);
	void button_4_clicked(wxCommandEvent &event);
	void button_5_clicked(wxCommandEvent &event);
	void button_6_clicked(wxCommandEvent &event);
	void rectangle_tool_selected(wxCommandEvent &event);
	void rounded_rectangle_tool_selected(wxCommandEvent &event);
	void ellipse_tool_selected(wxCommandEvent &event);
	void line_tool_selected(wxCommandEvent &event);
	void arrow_tool_selected(wxCommandEvent &event);
	void draw_tool_selected(wxCommandEvent &event);
	void color_button_clicked(wxCommandEvent &event);
	void undo(wxCommandEvent &event);
	wxColor getPrimaryColor();
	int getBrushSize();
	void createToolIcons();
};
