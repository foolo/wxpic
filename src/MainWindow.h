#pragma once
#include "MainWindowLayout.h"
#include "ImageStack.h"
#include "IStatusListener.h"
#include "Types.h"
#include <memory>
#include <vector>

class IconId {
public:
	enum {
		RECTANGLE,
		RECTANGLE_FILLED,
		ROUNDED_RECTANGLE,
		ELLIPSE,
		LINE,
		ARROW,
		DRAW,
		COLOR_PICKER,
		CROP,
		BLUR,
		MAX
	};
};

class MainWindow : public MainWindowLayout, public IUndoListener, public IStatusListener {
	ImageStack imageStack;
	const std::vector<int> brush_sizes{1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18};
	const int TOOL_STATUS_FIELD = 0;
	const int POSITION_STATUS_FIELD = 1;
	const int ZOOM_STATUS_FIELD = 2;
	std::vector<wxBitmap> icons;
	std::shared_ptr<ActiveFile> activeFile;
	wxStatusBar *statusBar;

private:
	void updateTitle();
	void updateSize();
	bool save();
	bool save_changes_prompt();
	bool save_as(const wxString &filePath);

public:
	MainWindow(wxWindow* parent, wxWindowID id, const wxString& title);
	virtual ~MainWindow();
	void init(std::shared_ptr<wxBitmap> bmp);
	void open(std::shared_ptr<LoadResult> loadResult);
	void newFile();
	void menu_new(wxCommandEvent &event);
	void menu_open(wxCommandEvent &event);
	void menu_save(wxCommandEvent &event);
	void menu_save_as(wxCommandEvent &event);
	void menu_about(wxCommandEvent &event);
	void menu_exit(wxCommandEvent &event);
	void exit();
	void on_close(wxCloseEvent& event);

	void rectangle_tool_selected(wxCommandEvent &event);
	void filled_rectangle_tool_selected(wxCommandEvent &event);
	void crop_tool_selected(wxCommandEvent &event);
	void blur_tool_selected(wxCommandEvent &event);
	void rounded_rectangle_tool_selected(wxCommandEvent &event);
	void ellipse_tool_selected(wxCommandEvent &event);
	void line_tool_selected(wxCommandEvent &event);
	void arrow_tool_selected(wxCommandEvent &event);
	void draw_tool_selected(wxCommandEvent &event);
	void color_picker_tool_selected(wxCommandEvent &event);
	void color_button_clicked(wxCommandEvent &event);
	void brush_size_changed(wxCommandEvent &event);
	void menu_undo(wxCommandEvent &event);
	void menu_redo(wxCommandEvent &event);
	void resized(wxSizeEvent& event);
	wxColor getPrimaryColor();
	void setPrimaryColor(const wxColor &color);
	int getBrushSize();
	void createToolIcons();
	void initCursor();

	// IUndoListener
	void notify();

	// IStatusListener
	void updatePositionStatus(const wxString& text);
	void updateZoomStatus(double zoomScale);
	void updateToolStatus(const wxString& text);
};
