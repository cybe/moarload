#ifndef MAIN_H
#define MAIN_H

#include <wx/app.h>

class Main : public wxApp
{
public:
    virtual bool OnInit();

private:
    // No assign (copy constructor inherited from wxApp)
    void operator=(const Main&);
};

#endif // MAIN_H
