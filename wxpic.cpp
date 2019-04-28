// -*- C++ -*-
//
// generated by wxGlade 0.8.3 on Sat Aug 11 20:59:08 2018
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

// This is an automatically generated file.
// Manual changes will be overwritten without warning!

#include <wx/wx.h>
#include <wx/image.h>
#include "MainWindow.h"


class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	std::cout << wxApp::argc << ", " << wxApp::argv[0] << std::endl;
	
    wxInitAllImageHandlers();
    MainWindow* mainWindow0 = new MainWindow(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(mainWindow0);
    mainWindow0->Show();
	mainWindow0->open(wxApp::argv[0]);
    return true;
}
