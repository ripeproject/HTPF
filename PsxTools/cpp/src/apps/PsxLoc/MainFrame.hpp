
#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif


// Define a new frame type: this is going to be our main frame
class MainFrame : public wxDialog
{
public:
	// ctor(s)
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	// event handlers (these functions should _not_ be virtual)
	void OnDone(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	void OnComputeScannerLocation(wxCommandEvent& event);
	void OnComputeScaleLocation(wxCommandEvent& event);

private:
	wxStaticText* mScannerText;
	wxStaticText* mScannerBlockLabel;
	wxTextCtrl* mScannerBlockEditBox;
	wxStaticText* mScannerColumnLabel;
	wxTextCtrl* mScannerColumnEditBox;
	wxStaticText* mScannerRowLabel;
	wxTextCtrl* mScannerRowEditBox;

	wxStaticText* mScaleText;
	wxStaticText* mScaleColumnLabel;
	wxTextCtrl* mScaleColumnEditBox;
	wxStaticText* mScaleRowLabel;
	wxTextCtrl* mScaleRowEditBox;

	wxButton* mDoneButton;

	uint8_t mScannerBlockNum;
	uint8_t mScannerColNum;
	uint8_t mScannerRowNum;

	wxString mScaleCol;
	uint8_t mScaleRow;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

