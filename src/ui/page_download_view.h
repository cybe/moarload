#ifndef PAGE_DOWNLOAD_VIEW_H
#define PAGE_DOWNLOAD_VIEW_H

//(*Headers(PageDownloadView)
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/listbox.h>
//*)

class PageDownloadView: public wxPanel
{
	public:

		PageDownloadView(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~PageDownloadView();

		//(*Declarations(PageDownloadView)
		wxSplitterWindow* filterAndDownloadsSplitter;
		wxListBox* filterList;
		wxListCtrl* downloadList;
		wxPanel* filterPanel;
		wxPanel* downloadsListPanel;
		//*)

	protected:

		//(*Identifiers(PageDownloadView)
		static const long ID_FILTER_LIST;
		static const long ID_FILTER_PANEL;
		static const long ID_DOWNLOAD_LIST;
		static const long ID_DOWNLOAD_LIST_PANEL;
		static const long ID_FILTER_AND_DOWNLOADS_SPLITTER;
		//*)

	private:

		//(*Handlers(PageDownloadView)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
