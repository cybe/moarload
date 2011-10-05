#include "page_download_view.h"

//(*InternalHeaders(PageDownloadView)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(PageDownloadView)
const long PageDownloadView::ID_FILTER_LIST = wxNewId();
const long PageDownloadView::ID_FILTER_PANEL = wxNewId();
const long PageDownloadView::ID_DOWNLOAD_LIST = wxNewId();
const long PageDownloadView::ID_DOWNLOAD_LIST_PANEL = wxNewId();
const long PageDownloadView::ID_FILTER_AND_DOWNLOADS_SPLITTER = wxNewId();
//*)

BEGIN_EVENT_TABLE(PageDownloadView,wxPanel)
	//(*EventTable(PageDownloadView)
	//*)
END_EVENT_TABLE()

PageDownloadView::PageDownloadView(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(PageDownloadView)
	wxBoxSizer* downloadPageSizer;
	wxBoxSizer* downloadSizer;
	wxBoxSizer* filterSizer;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	downloadPageSizer = new wxBoxSizer(wxVERTICAL);
	filterAndDownloadsSplitter = new wxSplitterWindow(this, ID_FILTER_AND_DOWNLOADS_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_FILTER_AND_DOWNLOADS_SPLITTER"));
	filterAndDownloadsSplitter->SetMinSize(wxSize(10,10));
	filterAndDownloadsSplitter->SetMinimumPaneSize(10);
	filterPanel = new wxPanel(filterAndDownloadsSplitter, ID_FILTER_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_FILTER_PANEL"));
	filterSizer = new wxBoxSizer(wxHORIZONTAL);
	filterList = new wxListBox(filterPanel, ID_FILTER_LIST, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_SINGLE|wxNO_BORDER, wxDefaultValidator, _T("ID_FILTER_LIST"));
	filterList->Append(_("All"));
	filterList->Append(_("Downloading"));
	filterList->Append(_("Complete"));
	filterList->Append(_("Paused"));
	filterSizer->Add(filterList, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	filterPanel->SetSizer(filterSizer);
	filterSizer->Fit(filterPanel);
	filterSizer->SetSizeHints(filterPanel);
	downloadsListPanel = new wxPanel(filterAndDownloadsSplitter, ID_DOWNLOAD_LIST_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_DOWNLOAD_LIST_PANEL"));
	downloadSizer = new wxBoxSizer(wxHORIZONTAL);
	downloadList = new wxListCtrl(downloadsListPanel, ID_DOWNLOAD_LIST, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DOWNLOAD_LIST"));
	downloadSizer->Add(downloadList, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	downloadsListPanel->SetSizer(downloadSizer);
	downloadSizer->Fit(downloadsListPanel);
	downloadSizer->SetSizeHints(downloadsListPanel);
	filterAndDownloadsSplitter->SplitVertically(filterPanel, downloadsListPanel);
	downloadPageSizer->Add(filterAndDownloadsSplitter, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(downloadPageSizer);
	downloadPageSizer->Fit(this);
	downloadPageSizer->SetSizeHints(this);
	//*)
}

PageDownloadView::~PageDownloadView()
{
	//(*Destroy(PageDownloadView)
	//*)
}

