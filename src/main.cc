#include "main.h"

#include <iostream>

#include "log.h"
#include "net/py_load_connector.h"
#include "net/cookie.h"

//(*AppHeaders
#include "ui/main_frame_view.h"
#include <wx/image.h>
//*)



// main in wxWidgets
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    configureLogging();

    LOG(logINFO) << "- moarload start -";

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

    //testing
    PyLoadConnector pyLoadConnector("zi0n.homelinux.net", 8081, "buildserver", "buildserver");

    Cookie cookie = Cookie::parse("beaker.session.id=ec5a316a58f5ec1ef77ead2a9b5fb582; expires=Tue, 19-Jan-2038 04:14:07 GMT; Path=/");
    LOG(logIO) << cookie.name;
    LOG(logIO) << cookie.value;
    LOG(logIO) << cookie.expires;
    LOG(logIO) << cookie.path;

    return wxsOK;
}

int Main::OnExit()
{
     LOG(logINFO) << "- moarload exit -" << std::endl;
     return 1;
}

void Main::configureLogging()
{
    Logger::setPidName("main");
    Logger::reportingLevel() = logIO;
    FILE* log_fd = fopen("moarload.log", "a");
    //FILE* log_fd = stdout;
    FileLog::stream() = log_fd;
}

