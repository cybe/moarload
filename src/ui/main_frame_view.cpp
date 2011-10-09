#include "main_frame_view.h"
#include <wx/msgdlg.h>

#include "model/download_list_model.h"
//(*InternalHeaders(MainFrameView)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f) {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(MainFrameView)
const long MainFrameView::ID_LISTBOX1 = wxNewId();
const long MainFrameView::ID_FILTER_PANEL = wxNewId();
const long MainFrameView::ID_CUSTOM1 = wxNewId();
const long MainFrameView::ID_DOWNLOAD_LIST_PANEL = wxNewId();
const long MainFrameView::ID_SPLITTERWINDOW1 = wxNewId();
const long MainFrameView::ID_DOWNLOAD_PANEL = wxNewId();
const long MainFrameView::ID_MAIN_NOTEBOOK = wxNewId();
const long MainFrameView::ID_STATICTEXT1 = wxNewId();
const long MainFrameView::ID_STATICTEXT2 = wxNewId();
const long MainFrameView::ID_STATICTEXT3 = wxNewId();
const long MainFrameView::ID_MAIN_STATUS_PANEL = wxNewId();
const long MainFrameView::ID_MAIN_FRAME_PANEL = wxNewId();
const long MainFrameView::idMenuQuit = wxNewId();
const long MainFrameView::idMenuAbout = wxNewId();
const long MainFrameView::ID_TOOLBARITEM1 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM3 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM4 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM5 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM6 = wxNewId();
const long MainFrameView::ID_MAIN_TOOLBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrameView, wxFrame)
    //(*EventTable(MainFrameView)
    //*)
END_EVENT_TABLE()

MainFrameView::MainFrameView(wxWindow* parent, wxWindowID id)
{

    //(*Initialize(MainFrameView)
    wxMenuItem* MenuItem2;
    wxBoxSizer* mainFrameSizer;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* mainStatusPanelSizer;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* mainMenuBar;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Moarload"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(640, 480));
    mainFramePanel = new wxPanel(this, ID_MAIN_FRAME_PANEL, wxPoint(80, 56), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_FRAME_PANEL"));
    mainFrameSizer = new wxBoxSizer(wxVERTICAL);
    mainNotebook = new wxNotebook(mainFramePanel, ID_MAIN_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAIN_NOTEBOOK"));
    downloadPanel = new wxPanel(mainNotebook, ID_DOWNLOAD_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_DOWNLOAD_PANEL"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    SplitterWindow1 = new wxSplitterWindow(downloadPanel, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10, 10));
    SplitterWindow1->SetMinimumPaneSize(10);
    filterPanel = new wxPanel(SplitterWindow1, ID_FILTER_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_FILTER_PANEL"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    ListBox1 = new wxListBox(filterPanel, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_SINGLE, wxDefaultValidator, _T("ID_LISTBOX1"));
    ListBox1->Append(_("All"));
    ListBox1->Append(_("Downloading"));
    ListBox1->Append(_("Completed"));
    ListBox1->Append(_("Paused"));
    BoxSizer2->Add(ListBox1, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 0);
    filterPanel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(filterPanel);
    BoxSizer2->SetSizeHints(filterPanel);
    downloadListPanel = new wxPanel(SplitterWindow1, ID_DOWNLOAD_LIST_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_DOWNLOAD_LIST_PANEL"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    //Custom1 = new wxDataViewCtrl(downloadListPanel,ID_CUSTOM1);
    //Custom1->AssociateModel(model);
    BoxSizer3->Add(BuildDataViewCtrl(downloadListPanel), 1, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
    downloadListPanel->SetSizer(BoxSizer3);
    BoxSizer3->Fit(downloadListPanel);
    BoxSizer3->SetSizeHints(downloadListPanel);
    SplitterWindow1->SplitVertically(filterPanel, downloadListPanel);
    BoxSizer1->Add(SplitterWindow1, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 0);
    downloadPanel->SetSizer(BoxSizer1);
    BoxSizer1->Fit(downloadPanel);
    BoxSizer1->SetSizeHints(downloadPanel);
    mainNotebook->AddPage(downloadPanel, _("Downloads"), false);
    mainFrameSizer->Add(mainNotebook, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
    mainStatusPanel = new wxPanel(mainFramePanel, ID_MAIN_STATUS_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_STATUS_PANEL"));
    mainStatusPanel->SetMinSize(wxSize(-1, 24));
    mainStatusPanel->SetMaxSize(wxSize(-1, 24));
    mainStatusPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(mainStatusPanel, ID_STATICTEXT1, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    mainStatusPanelSizer->Add(StaticText1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(mainStatusPanel, ID_STATICTEXT2, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    mainStatusPanelSizer->Add(StaticText2, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(mainStatusPanel, ID_STATICTEXT3, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    mainStatusPanelSizer->Add(StaticText3, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
    mainStatusPanel->SetSizer(mainStatusPanelSizer);
    mainStatusPanelSizer->Fit(mainStatusPanel);
    mainStatusPanelSizer->SetSizeHints(mainStatusPanel);
    mainFrameSizer->Add(mainStatusPanel, 0, wxEXPAND | wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL, 0);
    mainFramePanel->SetSizer(mainFrameSizer);
    mainFrameSizer->Fit(mainFramePanel);
    mainFrameSizer->SetSizeHints(mainFramePanel);
    mainMenuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    mainMenuBar->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    mainMenuBar->Append(Menu2, _("Help"));
    SetMenuBar(mainMenuBar);
    mainToolBar = new wxToolBar(this, ID_MAIN_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_TEXT | wxNO_BORDER, _T("ID_MAIN_TOOLBAR"));
    ToolBarItem1 = mainToolBar->AddTool(ID_TOOLBARITEM1, _("Start/Stop"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->AddSeparator();
    ToolBarItem2 = mainToolBar->AddTool(ID_TOOLBARITEM3, _("Stop Next"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem3 = mainToolBar->AddTool(ID_TOOLBARITEM4, _("Auto Reconnect"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ERROR")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem4 = mainToolBar->AddTool(ID_TOOLBARITEM5, _("Auto Clipboard"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->AddSeparator();
    ToolBarItem5 = mainToolBar->AddTool(ID_TOOLBARITEM6, _("Reconnect Now"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ERROR")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->Realize();
    SetToolBar(mainToolBar);

//    Connect(ID_LISTBOX1, wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&MainFrameView::OnListBox1Select1);
    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MainFrameView::OnQuit);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MainFrameView::OnAbout);
    //*)
}

MainFrameView::~MainFrameView()
{
    //(*Destroy(MainFrameView)
    //*)
}

void MainFrameView::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MainFrameView::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

wxDataViewCtrl* MainFrameView::BuildDataViewCtrl(wxPanel* parent)
{
    downloadDataViewCtrl = new wxDataViewCtrl(parent, ID_CUSTOM1);
    //wxASSERT(!downloadDataViewCtrl);

    DownloadListModel* downloadListModel = new DownloadListModel;
    
    downloadDataViewCtrl->AssociateModel(downloadListModel);

#if wxUSE_DRAG_AND_DROP && wxUSE_UNICODE
    downloadDataViewCtrl->EnableDragSource(wxDF_UNICODETEXT);
    downloadDataViewCtrl->EnableDropTarget(wxDF_UNICODETEXT);
#endif // wxUSE_DRAG_AND_DROP && wxUSE_UNICODE

    // column 0 of the view control:
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

    // column 1 of the view control:

    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column1 =
        new wxDataViewColumn("#", tr, 1, 30, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    column1->SetMinWidth(20);
    downloadDataViewCtrl->AppendColumn(column1);

    // column 2 of the view control:

    tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column2 =
        new wxDataViewColumn("Hoster", tr, 2, 150, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column2);

        tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column3 =
        new wxDataViewColumn("Priority", tr, 3, 150, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column3);
    
        tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column4 =
        new wxDataViewColumn("Status", tr, 4, 150, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column4);
    
        tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn* column5 =
        new wxDataViewColumn("Progress", tr, 5, 150, wxALIGN_LEFT,
                             wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
                             wxDATAVIEW_COL_RESIZABLE);
    downloadDataViewCtrl->AppendColumn(column5);
    
    // select initially the ninth symphony:
    //m_ctrl[0]->Select(m_music_model->GetNinthItem());

    return downloadDataViewCtrl;


    //wxDataViewModel* model = new DownloadListModel();
}
