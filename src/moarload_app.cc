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

#include "Pyload.h"  // As an example

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

//(*AppHeaders
#include "moarload_main.h"
#include <wx/image.h>
//*)

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

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

    boost::shared_ptr<TSocket> socket(new TSocket("10.10.2.1", 7227));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    PyloadClient client(protocol);
    try {
        transport->open();
        client.login("dennis", "foobar");
        std::string version;
        client.getServerVersion(version);
        std::cout << "pyload version: " << version << std::endl;
        transport->close();
    }
    catch (::apache::thrift::TException ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return wxsOK;
}
