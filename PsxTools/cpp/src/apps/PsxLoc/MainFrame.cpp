

// For compilers that support precompilation, includes "wx/wx.h".
#include "MainFrame.hpp"
#include <PsxTools/phenospex_utils.hpp>

#include <wx/valnum.h>

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// Custom Buttons items
	ID_DONE = wxID_HIGHEST + 1,

	ID_SCANNER_BLOCK,
	ID_SCANNER_COLUMN,
	ID_SCANNER_ROW,

	ID_SCALE_COLUMN,
	ID_SCALE_ROW,

};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MainFrame, wxDialog)
EVT_BUTTON(ID_DONE, MainFrame::OnDone)
EVT_CLOSE(MainFrame::OnClose)

EVT_TEXT(ID_SCANNER_BLOCK, OnComputeScaleLocation)
EVT_TEXT(ID_SCANNER_COLUMN, OnComputeScaleLocation)
EVT_TEXT(ID_SCANNER_ROW, OnComputeScaleLocation)

EVT_TEXT(ID_SCALE_COLUMN, OnComputeScannerLocation)
EVT_TEXT(ID_SCALE_ROW, OnComputeScannerLocation)

wxEND_EVENT_TABLE()


// frame constructor
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxDialog(NULL, wxID_ANY, title, pos, size)
{
	mScannerBlockNum = 0;
	mScannerColNum = 0;
	mScannerRowNum = 0;

	mScaleCol = "";
	mScaleRow = 0;

	mScannerText = new wxStaticText(this, wxID_ANY, _T("Scanner Location (Block : Column : Row )"), wxPoint(10,10)) ;

	mScannerBlockLabel = new wxStaticText(this, wxID_ANY, _T("Block:"), wxPoint(10, 40));

	wxIntegerValidator<uint8_t> blockValidator(&mScannerBlockNum, wxNUM_VAL_ZERO_AS_BLANK);
	blockValidator.SetRange(1, 47);

	mScannerBlockEditBox = new wxTextCtrl(this, ID_SCANNER_BLOCK, _T(""), wxPoint(45, 35), wxDefaultSize, 0, blockValidator);

	mScannerColumnLabel = new wxStaticText(this, wxID_ANY, _T("Column:"), wxPoint(170, 40));

	wxIntegerValidator<uint8_t> scanColValidator(&mScannerColNum, wxNUM_VAL_ZERO_AS_BLANK);
	scanColValidator.SetRange(1, 6);

	mScannerColumnEditBox = new wxTextCtrl(this, ID_SCANNER_COLUMN, _T(""), wxPoint(220, 35), wxDefaultSize, 0, scanColValidator);

	mScannerRowLabel = new wxStaticText(this, wxID_ANY, _T("Row:"), wxPoint(350, 40));

	wxIntegerValidator<uint8_t> scanRowValidator(&mScannerRowNum, wxNUM_VAL_ZERO_AS_BLANK);
	scanRowValidator.SetRange(1, 2);

	mScannerRowEditBox = new wxTextCtrl(this, ID_SCANNER_ROW, _T(""), wxPoint(380, 35), wxDefaultSize, 0, scanRowValidator);


	mScaleText = new wxStaticText(this, wxID_ANY, _T("Scale Location (Column : Row )"), wxPoint(10, 100));

	mScaleColumnLabel = new wxStaticText(this, wxID_ANY, _T("Column:"), wxPoint(10, 130));

	wxTextValidator scaleColValidator(wxFILTER_ASCII || wxFILTER_INCLUDE_CHAR_LIST , &mScaleCol);
	scaleColValidator.SetCharIncludes(_T("ABCDEFGHabcdefgh"));

	mScaleColumnEditBox = new wxTextCtrl(this, ID_SCALE_COLUMN, _T(""), wxPoint(60, 125), wxDefaultSize, 0, scaleColValidator);

	mScaleRowLabel = new wxStaticText(this, wxID_ANY, _T("Row:"), wxPoint(190, 130));

	wxIntegerValidator<uint8_t> scaleRowValidator(&mScaleRow, wxNUM_VAL_ZERO_AS_BLANK);
	scaleRowValidator.SetRange(1, 54);

	mScaleRowEditBox = new wxTextCtrl(this, ID_SCALE_ROW, _T(""), wxPoint(220, 125), wxDefaultSize, 0, scaleRowValidator);

	// normally we would initialize objects such as buttons and textboxes here 
	mDoneButton = new wxButton(this, ID_DONE, _T("Done"), wxPoint(415,180), wxDefaultSize, 0);
}


// event handlers

void MainFrame::OnDone(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Destroy();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnComputeScannerLocation(wxCommandEvent& event)
{
	if (!mScaleColumnEditBox->GetValidator()->TransferFromWindow() || (mScaleCol.size() > 1))
	{
		return;
	}

	if (!mScaleRowEditBox->GetValidator()->TransferFromWindow())
	{
		return;
	}

	auto result = ScaleToScannerPosition(mScaleCol[0], mScaleRow);

	if (result == INVALID_SCAN_POSITION)
	{
		mScannerBlockEditBox->ChangeValue("");
		mScannerColumnEditBox->ChangeValue("");
		mScannerRowEditBox->ChangeValue("");
		return;
	}

	mScannerBlockEditBox->ChangeValue(wxString::Format(wxT("%d"), result.block));
	mScannerColumnEditBox->ChangeValue(wxString::Format(wxT("%d"), result.col));
	mScannerRowEditBox->ChangeValue(wxString::Format(wxT("%d"), result.row));
}

void MainFrame::OnComputeScaleLocation(wxCommandEvent& event)
{
	if (!mScannerBlockEditBox->GetValidator()->TransferFromWindow())
	{
		return;
	}

	if (!mScannerColumnEditBox->GetValidator()->TransferFromWindow())
	{
		return;
	}

	if (!mScannerRowEditBox->GetValidator()->TransferFromWindow())
	{
		return;
	}

	auto result = ScannerToScalePosition(mScannerBlockNum, mScannerColNum, mScannerRowNum);

	if (result == INVALID_SCALE_POSITION)
	{
		mScaleColumnEditBox->ChangeValue("");
		mScaleRowEditBox->ChangeValue("");
		return;
	}

	mScaleColumnEditBox->ChangeValue(result.col);
	mScaleRowEditBox->ChangeValue(wxString::Format(wxT("%d"), result.row));

}
