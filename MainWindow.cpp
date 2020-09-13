#include "MainWindow.h"
#include "ShapeTool.h"
#include <wx/wfstream.h>
#include <wx/colordlg.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title)
 : MainWindowLayout(parent, id, title)
{
	imagePanel->setImageSource(&imageStack);
	Bind(wxEVT_BUTTON, &MainWindow::button_3_clicked, this, button_3->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_4_clicked, this, button_4->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_5_clicked, this, button_5->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::button_6_clicked, this, button_6->GetId());
	Bind(wxEVT_BUTTON, &MainWindow::color_button_clicked, this, color_button->GetId());
	Bind(wxEVT_MENU, &MainWindow::undo, this, wxID_UNDO);

	const int ENTRIES_CNT = 1;
	wxAcceleratorEntry entries[ENTRIES_CNT];
	entries[0].Set(wxACCEL_CTRL, (int) 'Z', wxID_UNDO);
	wxAcceleratorTable accel(ENTRIES_CNT, entries);
	SetAcceleratorTable(accel);

	for (unsigned i = 0; i < brush_sizes.size(); i++) {
		brush_size_choice->Append(wxString(std::to_string(brush_sizes[i])));
	}
	brush_size_choice->SetSelection(2);
	color_button->SetBackgroundColour(*wxRED);

	createToolIcons();
	wxToolBarToolBase *tmp_tool;

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::RECTANGLE), icons.at(IconId::RECTANGLE), wxITEM_RADIO, wxEmptyString, wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::rectangle_tool_selected, this, tmp_tool->GetId());

	tmp_tool = toolbar->AddTool(wxID_ANY, wxEmptyString, icons.at(IconId::ELLIPSE), icons.at(IconId::ELLIPSE), wxITEM_RADIO, wxEmptyString, wxEmptyString);
	Bind(wxEVT_MENU, &MainWindow::ellipse_tool_selected, this, tmp_tool->GetId());
}

MainWindow::~MainWindow()
{
}

void MainWindow::open(wxString filename)
{
	wxImage img;
	wxFFileInputStream fis(filename);
	wxPNGHandler pngHandler;
	if (pngHandler.LoadFile(&img, fis)) {
		std::shared_ptr<wxBitmap> bmp(new wxBitmap(img));
		imageStack.clear();
		imageStack.pushImage(bmp);
		imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::RECTANGLE));
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

void MainWindow::ellipse_tool_selected(wxCommandEvent &event) {
	event.Skip();
	imagePanel->setTool(new ShapeTool(&imageStack, imagePanel, this, ToolType::ELLIPSE));
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
		case IconId::RECTANGLE: dc.DrawRectangle(3, 4, 10, 8); break;
		case IconId::ELLIPSE: dc.DrawEllipse(2, 4, 12, 8); break;
		default: break;
		}
	}
}
