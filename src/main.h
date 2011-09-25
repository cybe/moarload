#ifndef MAIN_H
#define MAIN_H

// Dirty hack to avoid winsock.h being included twice.
// asio has to be included before wxwidgets.
#include <boost/asio.hpp>

#include <wx/app.h>

class Main : public wxApp
{
public:
    virtual bool OnInit();

private:
    void configureLogging();

    // No assign (copy constructor inherited from wxApp)
    void operator=(const Main&);
};

#endif // MAIN_H
