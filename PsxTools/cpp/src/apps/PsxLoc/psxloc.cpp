

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "MainFrame.hpp"

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type
class PsxLocApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
};

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// The PsxLoc Application
// ----------------------------------------------------------------------------

// `Main program' equivalent, creating windows and returning main app frame
bool PsxLocApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Create the main frame window
    MainFrame* frame = new MainFrame(_("Psx Location Converter"), wxDefaultPosition, wxSize(550, 280));

    // Show the frame
    frame->Show(true);

	SetTopWindow(frame);

    return true;
}


// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type
// (i.e. Sbf2NetApp and not wxApp)
wxIMPLEMENT_APP(PsxLocApp);

