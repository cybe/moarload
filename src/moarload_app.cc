/***************************************************************
 * Name:      moarloadApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2011-04-09
 * Copyright:  ()
 * License:
 **************************************************************/

#include "moarload_app.h"

#include <iostream>
#include <boost/thread.hpp>

#include "moarload_net.h"

//(*AppHeaders
#include "moarload_main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(moarloadApp)

void wait(int seconds)
{
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void thread()
{
    for (int i = 0; i < 10; ++i)
    {
        wait(1);
        std::cout << i << std::endl;
    }
}


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
    boost::thread t(thread);

    Net net;

    return wxsOK;
}
