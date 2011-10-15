#ifndef MAIN_FRAME_VIEW_H
#define MAIN_FRAME_VIEW_H

//(*Headers(MainFrameView)
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include "download_panel.h"
//*)

#include "../services/pyload_data_store.h"
#include "../services/pyload_requester.h"

class MainFrameView: public wxFrame {
public:
    MainFrameView(wxWindow* parent, wxWindowID id = -1);
    virtual ~MainFrameView();

private:
    PyloadDataStore m_dataStore;
    PyloadRequester m_requester;
    
    //(*Handlers(MainFrameView)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTextCtrl1Text(wxCommandEvent& event);
    void OnNotebook1PageChanged(wxNotebookEvent& event);
    void OnPanel2Paint(wxPaintEvent& event);
    void OnmainNotebookPageChanged(wxNotebookEvent& event);
    void OnListBox1Select(wxCommandEvent& event);
    void OnListBox1Select1(wxCommandEvent& event);
    void OnmainNotebookPageChanged1(wxNotebookEvent& event);
    void OnmainNotebookPageChanged2(wxNotebookEvent& event);
    void OnCustom1Paint(wxPaintEvent& event);
    //*)

    //(*Identifiers(MainFrameView)
    static const long ID_DOWNLOAD_PANEL;
    static const long ID_MAIN_NOTEBOOK;
    static const long ID_MAIN_FRAME_PANEL;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_TOOLBARITEM1;
    static const long ID_TOOLBARITEM3;
    static const long ID_TOOLBARITEM4;
    static const long ID_TOOLBARITEM5;
    static const long ID_TOOLBARITEM6;
    static const long ID_MAIN_TOOLBAR;
    static const long ID_MAIN_STATUS_BAR;
    //*)

    //(*Declarations(MainFrameView)
    wxToolBarToolBase* ToolBarItem5;
    wxStatusBar* mainStatusBar;
    wxToolBarToolBase* ToolBarItem2;
    wxPanel* mainFramePanel;
    wxToolBarToolBase* ToolBarItem4;
    wxToolBar* mainToolBar;
    wxToolBarToolBase* ToolBarItem1;
    wxToolBarToolBase* ToolBarItem3;
    DownloadPanel* downloadPanel;
    wxNotebook* mainNotebook;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_VIEW_H
