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

wxString wxbuildinfo(wxbuildinfoformat format) {
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
const long MainFrameView::ID_DOWNLOAD_PANEL = wxNewId();
const long MainFrameView::ID_MAIN_NOTEBOOK = wxNewId();
const long MainFrameView::ID_MAIN_FRAME_PANEL = wxNewId();
const long MainFrameView::idMenuQuit = wxNewId();
const long MainFrameView::idMenuAbout = wxNewId();
const long MainFrameView::ID_TOOLBARITEM1 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM3 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM4 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM5 = wxNewId();
const long MainFrameView::ID_TOOLBARITEM6 = wxNewId();
const long MainFrameView::ID_MAIN_TOOLBAR = wxNewId();
const long MainFrameView::ID_MAIN_STATUS_BAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrameView, wxFrame)
    //(*EventTable(MainFrameView)
    //*)
END_EVENT_TABLE()

MainFrameView::MainFrameView(wxWindow* parent, wxWindowID id) {
    //(*Initialize(MainFrameView)
    wxMenuItem* MenuItem2;
    wxBoxSizer* mainFrameSizer;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* mainMenuBar;
    wxMenu* Menu2;
    
    Create(parent, wxID_ANY, _("Moarload"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    mainFramePanel = new wxPanel(this, ID_MAIN_FRAME_PANEL, wxPoint(80,56), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_FRAME_PANEL"));
    mainFrameSizer = new wxBoxSizer(wxVERTICAL);
    mainNotebook = new wxNotebook(mainFramePanel, ID_MAIN_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAIN_NOTEBOOK"));
    downloadPanel = new DownloadPanel(mainNotebook);
    mainNotebook->AddPage(downloadPanel, _("Downloads"), false);
    mainFrameSizer->Add(mainNotebook, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
    mainToolBar = new wxToolBar(this, ID_MAIN_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_TEXT|wxNO_BORDER, _T("ID_MAIN_TOOLBAR"));
    ToolBarItem1 = mainToolBar->AddTool(ID_TOOLBARITEM1, _("Start/Stop"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->AddSeparator();
    ToolBarItem2 = mainToolBar->AddTool(ID_TOOLBARITEM3, _("Stop Next"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem3 = mainToolBar->AddTool(ID_TOOLBARITEM4, _("Auto Reconnect"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ERROR")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem4 = mainToolBar->AddTool(ID_TOOLBARITEM5, _("Auto Clipboard"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->AddSeparator();
    ToolBarItem5 = mainToolBar->AddTool(ID_TOOLBARITEM6, _("Reconnect Now"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ERROR")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    mainToolBar->Realize();
    SetToolBar(mainToolBar);
    mainStatusBar = new wxStatusBar(this, ID_MAIN_STATUS_BAR, wxST_SIZEGRIP, _T("ID_MAIN_STATUS_BAR"));
    int __wxStatusBarWidths_1[4] = { -10, -10, -10, -10 };
    int __wxStatusBarStyles_1[4] = { wxSB_FLAT, wxSB_FLAT, wxSB_FLAT, wxSB_FLAT };
    mainStatusBar->SetFieldsCount(4,__wxStatusBarWidths_1);
    mainStatusBar->SetStatusStyles(4,__wxStatusBarStyles_1);
    SetStatusBar(mainStatusBar);
    
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrameView::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrameView::OnAbout);
    //*)
}

MainFrameView::~MainFrameView() {
    //(*Destroy(MainFrameView)
    //*)
}

void MainFrameView::OnQuit(wxCommandEvent& event) {
    Close();
}

void MainFrameView::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void MainFrameView::OnmainNotebookPageChanged2(wxNotebookEvent& event)
{
}

void MainFrameView::OnCustom1Paint(wxPaintEvent& event)
{
}
