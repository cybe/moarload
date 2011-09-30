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
    std::string versionJson = pyLoadConnector.getServerVersion();
    LOG(logIO) << versionJson;

    ServerStatus statusServer = pyLoadConnector.statusServer();
    LOG(logIO) << statusServer.speed;
    LOG(logIO) << statusServer.download;

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
