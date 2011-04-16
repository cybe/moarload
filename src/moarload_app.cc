/***************************************************************
 * Name:      moarloadApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2011-04-09
 * Copyright:  ()
 * License:
 **************************************************************/

#include "moarload_app.h"

//(*AppHeaders
#include "moarload_main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(moarloadApp);

bool moarloadApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if (wxsOK)
    {
        moarloadFrame* Frame = new moarloadFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;
}
