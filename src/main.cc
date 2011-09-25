#include "main.h"

#include <iostream>

#include "log.h"
#include "net/http_client.h"

//(*AppHeaders
#include "ui/main_frame_view.h"
#include <wx/image.h>
//*)



// main in wxWidgets
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    configureLogging();

    LOG(logINFO) << "moarload start";

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

    HttpClient testClient;
    LOG(logINFO) << testClient.httpGet("http://zi0n.homelinux.net:8081/login");

    return wxsOK;
}

void Main::configureLogging()
{
    //Logger::setPidName("main");
    Logger::reportingLevel() = logDEBUG;
    FILE* log_fd = fopen("moarload.log", "a");
    //FILE* log_fd = stdout;
    FileLog::stream() = log_fd;
}

