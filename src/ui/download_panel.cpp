#include "download_panel.h"

//(*InternalHeaders(DownloadPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(DownloadPanel)
const long DownloadPanel::ID_FILTER_LIST_BOX = wxNewId();
//*)

BEGIN_EVENT_TABLE(DownloadPanel,wxPanel)
	//(*EventTable(DownloadPanel)
	//*)
END_EVENT_TABLE()

DownloadPanel::DownloadPanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DownloadPanel)
	wxBoxSizer* BoxSizer1;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	filterListBox = new wxListBox(this, ID_FILTER_LIST_BOX, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_SINGLE, wxDefaultValidator, _T("ID_FILTER_LIST_BOX"));
	filterListBox->SetSelection( filterListBox->Append(_("[ All ]")) );
	filterListBox->Append(_("Finished"));
	filterListBox->Append(_("Offline"));
	filterListBox->Append(_("Online"));
	filterListBox->Append(_("Queued"));
	filterListBox->Append(_("Skipped"));
	filterListBox->Append(_("Waiting"));
	filterListBox->Append(_("TempOffline"));
	filterListBox->Append(_("Starting"));
	filterListBox->Append(_("Failed"));
	filterListBox->Append(_("Aborted"));
	filterListBox->Append(_("Decrypting"));
	filterListBox->Append(_("Custom"));
	filterListBox->Append(_("Downloading"));
	filterListBox->Append(_("Processing"));
	filterListBox->Append(_("Unknown"));
	BoxSizer1->Add(filterListBox, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

DownloadPanel::~DownloadPanel()
{
	//(*Destroy(DownloadPanel)
	//*)
}

