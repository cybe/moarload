#include "main.h"

#include <iostream>

#include "log.h"

//(*AppHeaders
#include "ui/main_frame_view.h"
#include <wx/image.h>
//*)

// main in wxWidgets
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    Logger::setPidName("main");
    Logger::reportingLevel() = DEBUG;
    FILE* log_fd = stdout;
    FileLog::stream() = log_fd;

    LOG(INFO) << "moarload start";

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
