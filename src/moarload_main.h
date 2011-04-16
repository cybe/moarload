/***************************************************************
 * Name:      moarloadMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2011-04-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MOARLOADMAIN_H
#define MOARLOADMAIN_H

#include <nonexistant.h>

//(*Headers(moarloadFrame)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

class moarloadFrame: public wxFrame
{
public:

    moarloadFrame(wxWindow* parent, wxWindowID id = -1);
    virtual ~moarloadFrame();

private:

    //(*Handlers(moarloadFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    //*)

    //(*Identifiers(moarloadFrame)
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(moarloadFrame)
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // MOARLOADMAIN_H
