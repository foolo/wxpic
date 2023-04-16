// -*- C++ -*-
//
// generated by wxGlade
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#ifndef MAINWINDOWLAYOUT_H
#define MAINWINDOWLAYOUT_H

#include <wx/wx.h>
#include <wx/image.h>

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#include <wx/windowid.h>
#include "ImagePanel.h"
// end wxGlade


class MainWindowLayout: public wxFrame {
public:
				// begin wxGlade: MainWindowLayout::ids
				// end wxGlade

				MainWindowLayout(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:

protected:
				// begin wxGlade: MainWindowLayout::attributes
				wxMenuItem* menu_item_new;
				wxMenuItem* menu_item_open;
				wxMenuItem* menu_item_save;
				wxMenuItem* menu_item_save_as;
				wxMenuItem* menu_item_exit;
				wxMenuItem* menu_item_undo;
				wxMenuItem* menu_item_redo;
				wxMenuItem* menu_item_about;
				wxMenuBar* mainWindow0_menubar;
				wxToolBar* toolbar;
				wxButton* color_button;
				wxChoice* brush_size_choice;
				wxScrolledWindow* panel_1;
				ImagePanel* imagePanel;
				// end wxGlade
}; // wxGlade: end class


#endif // MAINWINDOWLAYOUT_H
