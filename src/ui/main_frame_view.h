#ifndef MAIN_FRAME_VIEW_H
#define MAIN_FRAME_VIEW_H

//(*Headers(MainFrameView)
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/stattext.h>
//*)

class MainFrameView: public wxFrame
{
public:

    MainFrameView(wxWindow* parent, wxWindowID id = -1);
    virtual ~MainFrameView();

private:

    //(*Handlers(MainFrameView)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTextCtrl1Text(wxCommandEvent& event);
    void OnNotebook1PageChanged(wxNotebookEvent& event);
    //*)

    //(*Identifiers(MainFrameView)
    static const long ID_PANEL2;
    static const long ID_PANEL3;
    static const long ID_PANEL4;
    static const long ID_PANEL5;
    static const long ID_MAIN_NOTEBOOK;
    static const long ID_STATICTEXT1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT3;
    static const long ID_MAIN_STATUS_PANEL;
    static const long ID_MAIN_FRAME_PANEL;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_TOOLBARITEM1;
    static const long ID_TOOLBARITEM3;
    static const long ID_TOOLBARITEM4;
    static const long ID_TOOLBARITEM5;
    static const long ID_TOOLBARITEM6;
    static const long ID_MAIN_TOOLBAR;
    //*)

    //(*Declarations(MainFrameView)
    wxToolBarToolBase* ToolBarItem5;
    wxPanel* settingsPanel;
    wxPanel* logPanel;
    wxPanel* downloadPanel;
    wxStaticText* StaticText1;
    wxToolBarToolBase* ToolBarItem2;
    wxStaticText* StaticText3;
    wxPanel* mainFramePanel;
    wxPanel* addPanel;
    wxToolBarToolBase* ToolBarItem4;
    wxToolBar* mainToolBar;
    wxToolBarToolBase* ToolBarItem1;
    wxStaticText* StaticText2;
    wxToolBarToolBase* ToolBarItem3;
    wxPanel* mainStatusPanel;
    wxNotebook* mainNotebook;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_VIEW_H
