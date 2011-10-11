#include "download_panel.h"

//(*InternalHeaders(DownloadPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(DownloadPanel)
//*)

BEGIN_EVENT_TABLE(DownloadPanel,wxPanel)
	//(*EventTable(DownloadPanel)
	//*)
END_EVENT_TABLE()

DownloadPanel::DownloadPanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(DownloadPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

DownloadPanel::~DownloadPanel()
{
	//(*Destroy(DownloadPanel)
	//*)
}

