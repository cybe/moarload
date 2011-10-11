#ifndef DOWNLOAD_PANEL_H
#define DOWNLOAD_PANEL_H

//(*Headers(DownloadPanel)
#include <wx/panel.h>
//*)

class DownloadPanel: public wxPanel
{
	public:

		DownloadPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DownloadPanel();

		//(*Declarations(DownloadPanel)
		//*)

	protected:

		//(*Identifiers(DownloadPanel)
		//*)

	private:

		//(*Handlers(DownloadPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
