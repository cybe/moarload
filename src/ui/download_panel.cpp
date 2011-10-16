#include "download_panel.h"

//(*InternalHeaders(DownloadPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

#include "model/download_list_model.h"

//(*IdInit(DownloadPanel)
const long DownloadPanel::ID_FILTER_LIST_BOX = wxNewId();
const long DownloadPanel::ID_DOWNLOAD_CONTROL = wxNewId();
//*)

BEGIN_EVENT_TABLE(DownloadPanel, wxPanel)
    //(*EventTable(DownloadPanel)
    //*)
END_EVENT_TABLE()

DownloadPanel::DownloadPanel(wxWindow* parent, PyloadDataStore& pyloadDataStore, wxWindowID id) :
    m_dataStore(pyloadDataStore) {
    //(*Initialize(DownloadPanel)
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
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
    downloadControl = buildDownloadControl(this, ID_DOWNLOAD_CONTROL);
    BoxSizer1->Add(downloadControl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    //*)
}

DownloadPanel::~DownloadPanel() {
    //(*Destroy(DownloadPanel)
    //*)
}

wxDataViewCtrl* DownloadPanel::buildDownloadControl(wxPanel* parent, wxWindowID id) {
    wxDataViewCtrl* downloadDataViewCtrl = new wxDataViewCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_ROW_LINES);
    //wxASSERT(!downloadDataViewCtrl);

    DownloadListModel* downloadListModel = new DownloadListModel(m_dataStore, downloadDataViewCtrl);

    downloadDataViewCtrl->AssociateModel(downloadListModel);
    downloadListModel->DecRef();

#if wxUSE_DRAG_AND_DROP && wxUSE_UNICODE
    downloadDataViewCtrl->EnableDragSource(wxDF_UNICODETEXT);
    downloadDataViewCtrl->EnableDropTarget(wxDF_UNICODETEXT);
#endif // wxUSE_DRAG_AND_DROP && wxUSE_UNICODE

    // column 0: name
    wxDataViewTextRenderer* tr =
        new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column0 =
        new wxDataViewColumn("Name", tr, 0, 200, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column0);

#if 0
    // Call this and sorting is enabled
    // immediatly upon start up.
    column0->SetAsSortKey();
#endif

    // column 1: #
    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column1 =
        new wxDataViewColumn("#", tr, 1, 30, wxALIGN_RIGHT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column1);

    // column 2: hoster
    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column2 =
        new wxDataViewColumn("Hoster", tr, 2, 200, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column2);

    // column 3: priority
    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column3 =
        new wxDataViewColumn("Priority", tr, 3, 80, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column3);

    // column 4: status
    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column4 =
        new wxDataViewColumn("Status", tr, 4, 80, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column4);

    // column 5: progress
    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column5 =
        new wxDataViewColumn("Progress", tr, 5, 150, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column5);

    // select initially the ninth symphony:
    //m_ctrl[0]->Select(m_music_model->GetNinthItem());

    return downloadDataViewCtrl;
}
