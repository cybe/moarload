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

#define BOOST_NETWORK_NO_LIB
#if defined(_WIN32)
#define __func__ __FUNCTION__
#endif
#include <boost/optional.hpp>
#include <boost/network/protocol/http/client.hpp>

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

    using namespace boost::network;
    http::client client;
    http::client::request request("http://google.de/");
    request << header("Connection", "close");
    http::client::response response = client.get(request);
    std::cout << body(response) << std::endl;

    return wxsOK;
}
