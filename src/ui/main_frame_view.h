#ifndef MAIN_FRAME_VIEW_H
#define MAIN_FRAME_VIEW_H

//(*Headers(MainFrameView)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
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
    //*)

    //(*Identifiers(MainFrameView)
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(MainFrameView)
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_VIEW_H