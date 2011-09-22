#include "main.h"

#include <iostream>

//(*AppHeaders
#include "moarload_main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Main)

bool Main::OnInit()
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
