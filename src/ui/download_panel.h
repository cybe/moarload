#ifndef DOWNLOAD_PANEL_H
#define DOWNLOAD_PANEL_H

//(*Headers(DownloadPanel)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listbox.h>
//*)

class DownloadPanel: public wxPanel
{
	public:

		DownloadPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~DownloadPanel();

		//(*Declarations(DownloadPanel)
		wxListBox* filterListBox;
		//*)

	protected:

		//(*Identifiers(DownloadPanel)
		static const long ID_FILTER_LIST_BOX;
		//*)

	private:

		//(*Handlers(DownloadPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
