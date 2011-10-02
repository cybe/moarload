#ifndef PY_LOAD_CONNECTOR_H
#define PY_LOAD_CONNECTOR_H

#include "thrift/pyload.h"

// thrift already generated an interface
class PyLoadConnector : public PyloadIf
{
    public:
        PyLoadConnector();
        virtual ~PyLoadConnector();

    protected:
    private:
};

#endif // PY_LOAD_CONNECTOR_H
