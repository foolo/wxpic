#include "MainWindow.h"
#include "ShapeTool.h"
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
	Bind(wxEVT_BUTTON, &MainWindow::button_3_clicked, this, button_3->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_4_clicked, this, button_4->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_5_clicked, this, button_5->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_6_clicked, this, button_6->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::color_button_clicked, this, color_button->GetId());
	Bind(wxEVT_MENU, &MainWindow::save, this, save_menu_item->GetId());
	Bind(wxEVT_MENU, &MainWindow::undo, this, undo_menu_item->GetId());
	Bind(wxEVT_MENU, &MainWindow::redo, this, redo_menu_item->GetId());
	Bind(wxEVT_SIZE, &MainWindow::resized, this);
	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::on_close, this);

	for (unsigned i = 0; i < brush_sizes.size(); i++) {
		brush_size_choice->Append(wxString(std::to_string(brush_sizes[i])));
	}
	brush_size_choice->SetSelection(2);
	color_button->SetBackgroundColour(*wxRED);

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
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateTitle() {
	if (!loadedFile) {
		SetTitle("");
	}
	else if (loadedFile->filename.empty()) {
		SetTitle("(new image)");
	}
	else {
		SetTitle(loadedFile->filename);
	}
}

void MainWindow::updateSize() {
	imagePanel->adjustImagePos();
	Layout();
	wxSize scrollbarSize(wxSystemSettings::GetMetric(wxSYS_VSCROLL_X), wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y));
	wxSize sizeDiff = imagePanel->GetSize() - panel_1->GetClientSize();
	wxSize newSize = GetSize() + sizeDiff + scrollbarSize;
	wxSize maxSize(1024, 768);
	wxSize minSize(640, 480);
	newSize.SetWidth(Util::limit(newSize.GetWidth(), minSize.GetWidth(), maxSize.GetWidth()));
	newSize.SetHeight(Util::limit(newSize.GetHeight(), minSize.GetHeight(), maxSize.GetHeight()));
	SetSize(newSize);
}

LoadedFile *MainWindow::loadBitmap(const wxString &filename) {
	if (filename.empty()) {
		wxBitmap *bmp = new wxBitmap(640, 480, 32);
		wxMemoryDC dc;
		dc.SelectObject(*bmp);
		dc.SetBackground(*wxWHITE_BRUSH);
		dc.Clear();
		return new LoadedFile(std::shared_ptr<wxBitmap>(bmp), filename, std::shared_ptr<wxImageHandler>());
	}
	else {
		return Util::loadBitmap(filename);
	}
}

void MainWindow::open(const wxString &filename) {
	imageStack.clear();
	loadedFile = std::shared_ptr<LoadedFile>(loadBitmap(filename));
	if (loadedFile) {
		imageStack.init(loadedFile->bitmap);
		wxCommandEvent tmp;
		draw_tool_selected(tmp);
		updateTitle();
		updateSize();
	}
	else {
		wxBitmap *bmp = new wxBitmap(16, 16, 32);
		wxMemoryDC dc;
		dc.SelectObject(*bmp);
		imageStack.init(std::shared_ptr<wxBitmap>(bmp));
		wxMessageBox("Could not load file\n" + filename, wxMessageBoxCaptionStr, wxICON_ERROR);
		Close();
	}
}

bool MainWindow::save() {
	std::shared_ptr<wxBitmap> image = imageStack.getImage();
	if (loadedFile->filename.IsEmpty()) {
		wxMessageBox("saving unnamed file not implemented", wxMessageBoxCaptionStr, wxICON_ERROR);
		return false;
	}
	else {
		Util::saveBitmap(imageStack.getImage().get(), loadedFile->filename, *loadedFile->imageHandler);
		imageStack.markSaved();
		return true;
	}
}

void MainWindow::save(wxCommandEvent &event) {
	event.Skip();
	save();
}

void MainWindow::on_close(wxCloseEvent &event) {
	if (imageStack.isModified()) {
		wxMessageDialog dialog(this, "Save changes?", "Save changes", wxYES_NO | wxCANCEL);
		int result = dialog.ShowModal();
		if (result == wxID_YES) {
			if (save()) {
				Destroy();
			}
		}
		else if (result == wxID_NO)  {
			Destroy();
		}
		else {
			// cancel, do nothing
		}
	}
	else {
		Destroy();
	}
}

void MainWindow::button_3_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_3_clicked" << std::endl;
}

void MainWindow::button_4_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_4_clicked" << std::endl;
}

void MainWindow::button_5_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_5_clicked" << std::endl;
}

void MainWindow::button_6_clicked(wxCommandEvent &event) {
	event.Skip();
	std::cout << "button_6_clicked" << std::endl;
}

void MainWindow::rectangle_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::RECTANGLE));
}

void MainWindow::rounded_rectangle_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::ROUNDED_RECTANGLE));
}

void MainWindow::ellipse_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::ELLIPSE));
}

void MainWindow::line_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::LINE));
}

void MainWindow::arrow_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::ARROW));
}

void MainWindow::draw_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new DrawTool(&imageStack, imagePanel, this));
}

void MainWindow::color_button_clicked(wxCommandEvent &event) {
	event.Skip();
	wxColour color = wxGetColourFromUser(this, color_button->GetBackgroundColour());
	if (color.IsOk()) {
		color_button->SetBackgroundColour(color);
	}
}

void MainWindow::undo(wxCommandEvent &event) {
	event.Skip();
	imageStack.popImage();
	imagePanel->Refresh();
}

void MainWindow::redo(wxCommandEvent &event) {
	event.Skip();
	imageStack.redo();
	imagePanel->Refresh();
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
