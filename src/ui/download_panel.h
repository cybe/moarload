#ifndef DOWNLOAD_PANEL_H
#define DOWNLOAD_PANEL_H

//(*Headers(DownloadPanel)
#include <wx/dataview.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listbox.h>
//*)

#include "../services/pyload_data_store.h"

class DownloadListModel;

class DownloadPanel: public wxPanel {
public:
    DownloadPanel(wxWindow* parent, PyloadDataStore& pyloadDataStore, wxWindowID id = wxID_ANY);
    virtual ~DownloadPanel();

    //(*Declarations(DownloadPanel)
    wxListBox* filterListBox;
    wxDataViewCtrl* downloadControl;
    //*)

protected:
    //(*Identifiers(DownloadPanel)
    static const long ID_FILTER_LIST_BOX;
    static const long ID_DOWNLOAD_CONTROL;
    //*)

private:
    //(*Handlers(DownloadPanel)
    void OnPaint(wxPaintEvent& event);
    //*)

    PyloadDataStore& m_dataStore;

    wxDataViewCtrl* buildDownloadControl(wxPanel* parent, wxWindowID id = wxID_ANY);

    DECLARE_EVENT_TABLE()
};

#endif
