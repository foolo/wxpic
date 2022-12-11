#pragma once
#include "MainWindowLayout.h"
#include "ImageStack.h"
#include "Types.h"
#include <memory>
#include <vector>

enum class ToolType { RECTANGLE, ROUNDED_RECTANGLE, ELLIPSE, LINE, ARROW };

class IconId {
public:
	enum { RECTANGLE, ROUNDED_RECTANGLE, ELLIPSE, LINE, ARROW, DRAW, CROP, MAX };
};

class MainWindow : public MainWindowLayout, public IUndoListener {
	ImageStack imageStack;
	const std::vector<int> brush_sizes{1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18};
	std::vector<wxBitmap> icons;
	std::shared_ptr<ActiveFile> activeFile;

private:
	void updateTitle();
	void updateSize();
	bool save();
	bool save_as(const wxString &filePath);

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void init(std::shared_ptr<wxBitmap> bmp);
	void open(std::shared_ptr<LoadResult> loadResult);
	void newFile();
	void save(wxCommandEvent &event);
	void save_as(wxCommandEvent &event);
	void exit(wxCommandEvent &event);
	void exit();
	void on_close(wxCloseEvent& event);

	void button_3_clicked(wxCommandEvent &event);
	void button_4_clicked(wxCommandEvent &event);
	void button_5_clicked(wxCommandEvent &event);
	void button_6_clicked(wxCommandEvent &event);
	void rectangle_tool_selected(wxCommandEvent &event);
	void crop_tool_selected(wxCommandEvent &event);
	void rounded_rectangle_tool_selected(wxCommandEvent &event);
	void ellipse_tool_selected(wxCommandEvent &event);
	void line_tool_selected(wxCommandEvent &event);
	void arrow_tool_selected(wxCommandEvent &event);
	void draw_tool_selected(wxCommandEvent &event);
	void color_button_clicked(wxCommandEvent &event);
	void undo(wxCommandEvent &event);
	void redo(wxCommandEvent &event);
	void resized(wxSizeEvent& event);
	wxColor getPrimaryColor();
	int getBrushSize();
	void createToolIcons();
	void initCursor();

	// IUndoListener
	void notify();
};
