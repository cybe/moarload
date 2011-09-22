#include "main.h"

#include <iostream>

//(*AppHeaders
#include "ui/main_frame_view.h"
#include <wx/image.h>
//*)

// main in wxWidgets
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if (wxsOK)
    {
        MainFrameView* view = new MainFrameView(0);
        view->Show();
        SetTopWindow(view);
    }
    //*)

    return wxsOK;
}
