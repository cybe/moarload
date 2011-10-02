#include "main.h"

#include <iostream>

#include "log.h"
#include "net/py_load_connector.h"
#include "net/py_load_http_connector.h"
#include "net/py_load_thrift_connector.h"

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
    LOG(logIO) << "-----http:";
    PyLoadConnector* con = new PyLoadHttpConnector("buildserver", 8081);
    bool loginSuccesfull = con->login("buildserver", "buildserver");
    LOG(logIO) << "Login: " << loginSuccesfull;
    std::string version;
    con->getServerVersion(version);
    LOG(logIO) << "version: " << version;
    delete con;

    LOG(logIO) << "-----thrift:";
    con = new PyLoadThriftConnector("buildserver", 7227);
    loginSuccesfull = con->login("buildserver", "buildserver");
    LOG(logIO) << "Login: " << loginSuccesfull;
    con->getServerVersion(version);
    LOG(logIO) << "version: " << version;
    delete con;

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
