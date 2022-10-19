

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include "wx/log.h"
#endif

#include <wx/cmdline.h>


// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type
class PsxPlannerApp : public wxApp
{
public:
	PsxPlannerApp();
	virtual ~PsxPlannerApp();

	virtual void OnInitCmdLine(wxCmdLineParser& parser) wxOVERRIDE;
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser) wxOVERRIDE;
	virtual bool OnInit() wxOVERRIDE;

private:
};

// Define a new frame type: this is going to be our main frame
class MainFrame : public wxFrame
{
public:
	// ctor(s)
	explicit MainFrame();
	virtual ~MainFrame();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& evt);

private:
	wxTextCtrl* mpLogCtrl;
	wxLog*		mpOriginalLog;

	wxEvtHandler* mpHandler;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	ID_QUIT = wxID_EXIT,

	// it is important for the id corresponding to the "About" command to have
	// this standard value as otherwise it won't be handled properly under Mac
	// (where it is special and put into the "Apple" menu)
	ID_ABOUT = wxID_ABOUT,

	// Custom submenu items
	ID_RECONNECT = wxID_HIGHEST + 1,

};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_QUIT, MainFrame::OnQuit)
EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// The Sbf2Net Application
// ----------------------------------------------------------------------------

PsxPlannerApp::PsxPlannerApp()
{
}

PsxPlannerApp::~PsxPlannerApp()
{
}

// command line arguments handling
void PsxPlannerApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    wxApp::OnInitCmdLine(parser);
}

bool PsxPlannerApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if (!wxApp::OnCmdLineParsed(parser))
        return false;

	return true;
}

// `Main program' equivalent, creating windows and returning main app frame
bool PsxPlannerApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Create the main frame window
    MainFrame* frame = new MainFrame();

    // Show the frame
    frame->Show(true);

    return true;
}


// ----------------------------------------------------------------------------
// Main Frame
// ----------------------------------------------------------------------------

// frame constructor
MainFrame::MainFrame()
	: wxFrame(NULL, wxID_ANY, "Psx Planner"),
	mpLogCtrl(nullptr),
	mpOriginalLog(nullptr)
{

	mpHandler = GetEventHandler();

	// set the frame icon
	SetIcon(wxICON(psx_planner));

#if wxUSE_MENUBAR
	// create a menu bar
	wxMenu* fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(ID_ABOUT, "&About\tF1", "Show about dialog");

	wxMenuItem* reconnect = fileMenu->Append(ID_RECONNECT, "&Reconnect\tAlt-R", "Reconnect to the GPS");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_QUIT, "E&xit\tAlt-X", "Quit this program");

	// now append the freshly created menu to the menu bar...
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

#else // !wxUSE_MENUBAR
	// If menus are not available add a button to access the about box
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* aboutBtn = new wxButton(this, wxID_ANY, "About...");
	aboutBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAbout, this);
	sizer->Add(aboutBtn, wxSizerFlags().Center());
	SetSizer(sizer);
#endif // wxUSE_MENUBAR/!wxUSE_MENUBAR

	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar();

	// redirect logs from our event handlers to text control
	mpLogCtrl = new wxTextCtrl(this, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	mpLogCtrl->SetMinSize(wxSize(-1, 100));
	mpOriginalLog = wxLog::SetActiveTarget(new wxLogTextCtrl(mpLogCtrl));

	// It is also possible to use event tables, but dynamic binding is simpler.
//	Bind(wxEVT_THREAD, &MainFrame::OnThreadUpdate, this);
}

MainFrame::~MainFrame()
{
	delete wxLog::SetActiveTarget(mpOriginalLog);
}



// event handlers


void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		"Welcome to PSX Planner\n"
		"\n"
		"Plan your experiment for the HTPF Phenospex(c) system.\n"
		"Version 1.0"
	),
		"About PsxPlanner",
		wxOK | wxICON_INFORMATION,
		this);
}


void MainFrame::OnClose(wxCloseEvent&)
{
	Destroy();
}


// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type
// (i.e. Sbf2NetApp and not wxApp)
wxIMPLEMENT_APP(PsxPlannerApp);
