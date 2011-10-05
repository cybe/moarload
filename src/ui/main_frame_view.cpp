#include "main_frame_view.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(MainFrameView)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f)
    {
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
const long MainFrameView::ID_PANEL2 = wxNewId();
const long MainFrameView::ID_PANEL3 = wxNewId();
const long MainFrameView::ID_PANEL4 = wxNewId();
const long MainFrameView::ID_PANEL5 = wxNewId();
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
    wxMenu* Menu1;
    wxBoxSizer* mainStatusPanelSizer;
    wxMenuBar* mainMenuBar;
    wxMenu* Menu2;
    
    Create(parent, wxID_ANY, _("Moarload"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(318,260));
    mainFramePanel = new wxPanel(this, ID_MAIN_FRAME_PANEL, wxPoint(80,56), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_FRAME_PANEL"));
    mainFrameSizer = new wxBoxSizer(wxVERTICAL);
    mainNotebook = new wxNotebook(mainFramePanel, ID_MAIN_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAIN_NOTEBOOK"));
    downloadPanel = new wxPanel(mainNotebook, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    addPanel = new wxPanel(mainNotebook, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    settingsPanel = new wxPanel(mainNotebook, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    logPanel = new wxPanel(mainNotebook, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    mainNotebook->AddPage(downloadPanel, _("Download"), false);
    mainNotebook->AddPage(addPanel, _("Add"), false);
    mainNotebook->AddPage(settingsPanel, _("Settings"), false);
    mainNotebook->AddPage(logPanel, _("Log"), false);
    mainFrameSizer->Add(mainNotebook, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainStatusPanel = new wxPanel(mainFramePanel, ID_MAIN_STATUS_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MAIN_STATUS_PANEL"));
    mainStatusPanel->SetMinSize(wxSize(-1,24));
    mainStatusPanel->SetMaxSize(wxSize(-1,24));
    mainStatusPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(mainStatusPanel, ID_STATICTEXT1, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    mainStatusPanelSizer->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(mainStatusPanel, ID_STATICTEXT2, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    mainStatusPanelSizer->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(mainStatusPanel, ID_STATICTEXT3, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    mainStatusPanelSizer->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    mainStatusPanel->SetSizer(mainStatusPanelSizer);
    mainStatusPanelSizer->Fit(mainStatusPanel);
    mainStatusPanelSizer->SetSizeHints(mainStatusPanel);
    mainFrameSizer->Add(mainStatusPanel, 0, wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 0);
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
    
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrameView::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainFrameView::OnAbout);
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

void MainFrameView::OnTextCtrl1Text(wxCommandEvent& event)
{
}
