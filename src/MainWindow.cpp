#include "MainWindow.h"
#include "ShapeTool.h"
#include "CropTool.h"
#include "DrawTool.h"
#include "Util.h"
#include "image_data.h"
#include <wx/wfstream.h>
#include <wx/colordlg.h>
#include <wx/display.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title)
 : MainWindowLayout(parent, id, title)
{
	imagePanel->setImageSource(&imageStack);
	imageStack.setUndoListener(this);
	Bind(wxEVT_BUTTON, &MainWindow::button_3_clicked, this, button_3->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_4_clicked, this, button_4->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_5_clicked, this, button_5->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_6_clicked, this, button_6->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::color_button_clicked, this, color_button->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_new, this, menu_item_new->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_open, this, menu_item_open->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_save, this, menu_item_save->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_save_as, this, menu_item_save_as->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_exit, this, menu_item_exit->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_undo, this, menu_item_undo->GetId());
	Bind(wxEVT_MENU, &MainWindow::menu_redo, this, menu_item_redo->GetId());
	Bind(wxEVT_SIZE, &MainWindow::resized, this);
	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::on_close, this);

	for (unsigned i = 0; i < brush_sizes.size(); i++) {
		brush_size_choice->Append(wxString(std::to_string(brush_sizes[i])));
	}
	brush_size_choice->SetSelection(2);
	color_button->SetBackgroundColour(*wxRED);

	statusBar = CreateStatusBar();
	std::vector<int> statusBarWidths{ -1, 100, 100 };
	std::vector<int> statusFieldStyles{ wxSB_SUNKEN, wxSB_SUNKEN, wxSB_SUNKEN };
	statusBar->SetFieldsCount(statusBarWidths.size(), &statusBarWidths.front());
	statusBar->SetStatusStyles(statusFieldStyles.size(), &statusFieldStyles.front());

	createToolIcons();
	initCursor();

	wxToolBarToolBase *tmp_tool;

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::DRAW), icons.at(IconId::DRAW), wxITEM_RADIO, "Draw", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::draw_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::RECTANGLE), icons.at(IconId::RECTANGLE), wxITEM_RADIO, "Rectangle", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::rectangle_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::ROUNDED_RECTANGLE), icons.at(IconId::ROUNDED_RECTANGLE), wxITEM_RADIO, "Rounded rectangle", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::rounded_rectangle_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::ELLIPSE), icons.at(IconId::ELLIPSE), wxITEM_RADIO, "Ellipse", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::ellipse_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::LINE), icons.at(IconId::LINE), wxITEM_RADIO, "Line", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::line_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::ARROW), icons.at(IconId::ARROW), wxITEM_RADIO, "Arrow", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::arrow_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::CROP), icons.at(IconId::CROP), wxITEM_RADIO, "Crop", wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::crop_tool_selected, this, tmp_tool->GetId());
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateTitle() {
	std::string modifiedPrefix = imageStack.isModified() ? "* " : "";
	if (!activeFile) {
		SetTitle(modifiedPrefix + "(new image)");
	}
	else {
		SetTitle(modifiedPrefix + activeFile->path);
	}
}

void MainWindow::updateSize() {
	imagePanel->adjustImagePos();
	Layout();
	wxSize scrollbarSize(wxSystemSettings::GetMetric(wxSYS_VSCROLL_X), wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y));
	wxPoint windowCenterPos(GetScreenRect().GetX() + GetScreenRect().GetWidth() / 2, GetScreenRect().GetY() + GetScreenRect().GetHeight() / 2) ;
	int displayId = wxDisplay::GetFromPoint(windowCenterPos);
	wxDisplay display(displayId);
	wxSize sizeDiff = imagePanel->GetSize() - panel_1->GetClientSize();
	wxSize newSize = GetSize() + sizeDiff + scrollbarSize;
	wxSize maxSize = display.GetGeometry().GetSize();
	wxSize minSize(640, 480);
	newSize.SetWidth(Util::limit(newSize.GetWidth(), minSize.GetWidth(), maxSize.GetWidth()));
	newSize.SetHeight(Util::limit(newSize.GetHeight(), minSize.GetHeight(), maxSize.GetHeight()));
	SetSize(newSize);
}

std::shared_ptr<wxBitmap> createEmptyBitmap() {
	std::shared_ptr<wxBitmap> bmp(new wxBitmap(640, 480, 32));
	wxMemoryDC dc;
	dc.SelectObject(*bmp);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	return bmp;
}

void MainWindow::init(std::shared_ptr<wxBitmap> bmp) {
	imageStack.init(bmp);
	wxCommandEvent tmp;
	draw_tool_selected(tmp);
	updateTitle();
	updateSize();
	imagePanel->setStatusListener(this);
}

void MainWindow::open(std::shared_ptr<LoadResult> loadResult) {
	activeFile = std::shared_ptr<ActiveFile>(new ActiveFile(loadResult->path, loadResult->imageHandler));
	init(loadResult->bitmap);
}

void MainWindow::newFile() {
	init(createEmptyBitmap());
}

bool MainWindow::save_as(const wxString &filePath) {
	wxFileDialog dialog(this, "Save file", "", filePath, "", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (dialog.ShowModal() == wxID_CANCEL) {
		return false;
	}
	wxString path = dialog.GetPath();
	wxString filename = dialog.GetFilename();
	std::shared_ptr<wxImageHandler> imageHandler = Util::filenameToHandler(filename);
	if (!imageHandler) {
		wxMessageBox("Filetype not recognized from filename:\n\"" + filename + "\"", wxMessageBoxCaptionStr, wxICON_ERROR);
		return false;
	}
	try {
		Util::saveBitmap(imageStack.getImage().get(), path, *imageHandler);
		activeFile = std::shared_ptr<ActiveFile>(new ActiveFile(path, imageHandler));
		imageStack.markSaved();
		return true;
	}
	catch (const IOException &ex) {
		wxMessageBox("Could not save \"" + filename + "\"\n" + ex.what(), wxMessageBoxCaptionStr, wxICON_ERROR);
		return false;
	}
	return false;
}

bool MainWindow::save() {
	std::shared_ptr<wxBitmap> image = imageStack.getImage();
	if (!activeFile) {
		return save_as("");
	}
	try {
		Util::saveBitmap(imageStack.getImage().get(), activeFile->path, *activeFile->imageHandler);
		imageStack.markSaved();
		return true;
	}
	catch (const IOException &ex) {
		wxMessageBox("Could not save \"" + activeFile->path + "\"\n" + ex.what(), wxMessageBoxCaptionStr, wxICON_ERROR);
		return false;
	}
}

bool MainWindow::save_changes_prompt() {
	if (imageStack.isModified() == false) {
		return true;
	}
	wxMessageDialog dialog(this, "Save changes?", "Save changes", wxYES_NO | wxCANCEL);
	switch(dialog.ShowModal()) {
		case wxID_YES:
			return save();
		case wxID_NO:
			return true;
		case wxID_CANCEL:
		default:
			return false;
	}
}

void MainWindow::menu_new(wxCommandEvent &event) {
	if (save_changes_prompt()) {
		newFile();
	}
}

void MainWindow::menu_open(wxCommandEvent &event) {
	if (save_changes_prompt()) {
		wxFileDialog dialog(this, "Open file", "", (activeFile ? activeFile->path : ""), "", wxFD_OPEN|wxFD_OVERWRITE_PROMPT);
		if (dialog.ShowModal() == wxID_CANCEL) {
			return;
		}
		wxString path = dialog.GetPath();
		wxString filename = dialog.GetFilename();
		std::shared_ptr<wxImageHandler> imageHandler = Util::filenameToHandler(filename);
		if (!imageHandler) {
			wxMessageBox("Filetype not recognized for " + filename, wxMessageBoxCaptionStr, wxICON_ERROR);
			return;
		}
		std::shared_ptr<LoadResult> loadResult = Util::loadBitmap(path);
		if (!loadResult) {
			wxMessageBox("Could not load file\n\"" + path + "\"", "wxpic loading error", wxICON_ERROR);
			return;
		}
		open(loadResult);
	}
}

void MainWindow::menu_save(wxCommandEvent &event) {
	save();
}

void MainWindow::menu_save_as(wxCommandEvent &event) {
	save_as(activeFile ? activeFile->path : "");
}

void MainWindow::menu_exit(wxCommandEvent &event) {
	exit();
}

void MainWindow::exit() {
	if (save_changes_prompt()) {
		Destroy();
	}
}

void MainWindow::on_close(wxCloseEvent &event) {
	exit();
}

void MainWindow::button_3_clicked(wxCommandEvent &event) {
	std::cout << "button_3_clicked" << std::endl;
}

void MainWindow::button_4_clicked(wxCommandEvent &event) {
	std::cout << "button_4_clicked" << std::endl;
}

void MainWindow::button_5_clicked(wxCommandEvent &event) {
	std::cout << "button_5_clicked" << std::endl;
}

void MainWindow::button_6_clicked(wxCommandEvent &event) {
	std::cout << "button_6_clicked" << std::endl;
}

void MainWindow::rectangle_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new ShapeTool(&imageStack, this, ToolType::RECTANGLE));
}

void MainWindow::crop_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new CropTool(&imageStack, this));
}

void MainWindow::rounded_rectangle_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new ShapeTool(&imageStack, this, ToolType::ROUNDED_RECTANGLE));
}

void MainWindow::ellipse_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new ShapeTool(&imageStack, this, ToolType::ELLIPSE));
}

void MainWindow::line_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new ShapeTool(&imageStack, this, ToolType::LINE));
}

void MainWindow::arrow_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new ShapeTool(&imageStack, this, ToolType::ARROW));
}

void MainWindow::draw_tool_selected(wxCommandEvent &event) {
	imagePanel->setTool(new DrawTool(&imageStack, this));
}

void MainWindow::color_button_clicked(wxCommandEvent &event) {
	wxColour color = wxGetColourFromUser(this, color_button->GetBackgroundColour());
	if (color.IsOk()) {
		color_button->SetBackgroundColour(color);
	}
}

void MainWindow::menu_undo(wxCommandEvent &event) {
	imagePanel->undo();
}

void MainWindow::menu_redo(wxCommandEvent &event) {
	imagePanel->redo();
}

void MainWindow::resized(wxSizeEvent& event) {
	event.Skip();
	imagePanel->windowResized(event);
}

wxColor MainWindow::getPrimaryColor() {
	return color_button->GetBackgroundColour();
}

int MainWindow::getBrushSize() {
	return brush_sizes.at(brush_size_choice->GetSelection());
}

void MainWindow::createToolIcons() {
	for (int i = 0; i < IconId::MAX; i++) {
		icons.push_back(wxBitmap(16, 16, 32));
		wxMemoryDC dc;
		dc.SelectObject(icons.back());
		dc.SetBackground(*wxTRANSPARENT_BRUSH);
		dc.Clear();
		dc.SetPen(wxPen(*wxBLACK));
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		switch (i) {
		case IconId::RECTANGLE: dc.DrawRectangle(1, 3, 14, 10); break;
		case IconId::ROUNDED_RECTANGLE: dc.DrawRoundedRectangle(0, 3, 16, 10, 3); break;
		case IconId::ELLIPSE: dc.DrawEllipse(0, 3, 15, 10); break;
		case IconId::LINE: dc.DrawLine(0, 13, 15, 3); break;
		case IconId::ARROW:
			dc.DrawLine(0, 8, 15, 8);
			dc.DrawLine(15, 8, 12, 5);
			dc.DrawLine(15, 8, 12, 11);
			break;
		case IconId::DRAW: {
			const int d = 2;
			const int s1x = 0+d;
			const int s1y = 11-d;
			const int s2x = 4+d;
			const int s2y = 15-d;
			dc.DrawLine(0, 15, s2x, s2y);
			dc.DrawLine(0, 15, s1x, s1y);
			dc.DrawLine(s1x, s1y, s2x, s2y);
			dc.DrawLine(s1x, s1y, 11, 0);
			dc.DrawLine(s2x, s2y, 15, 4);
			dc.DrawLine(11, 0, 15, 4);
		}
		break;
		case IconId::CROP: {
			int x1 = 3;
			int y1 = 3;
			int x2 = 12;
			int y2 = 10;
			int o = 3;
			dc.DrawLine(x1-o, y1, x2, y1);
			dc.DrawLine(x1, y2, x2+o, y2);
			dc.DrawLine(x1, y1-o, x1, y2);
			dc.DrawLine(x2, y1, x2, y2+o);
		}
		default: break;
		}
	}
}

void MainWindow::initCursor() {
	wxImage img = wxBitmap::NewFromPNGData(res_crosshair_png, res_crosshair_png_len).ConvertToImage();
	img.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 8);
	img.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 8);
	imagePanel->SetCursor(wxCursor(img));
}

void MainWindow::notify() {
	updateTitle();
}

void MainWindow::updatePositionStatus(const wxString& text) {
	statusBar->SetStatusText(text, POSITION_STATUS_FIELD);
}

void MainWindow::updateZoomStatus(double zoomScale) {
	statusBar->SetStatusText(std::to_string((int)(zoomScale * 100 + 0.5)) + "%", ZOOM_STATUS_FIELD);
}

void MainWindow::updateToolStatus(const wxString& text) {
	statusBar->SetStatusText(text, TOOL_STATUS_FIELD);
}
