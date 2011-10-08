#ifndef PYLOAD_DATA_STORE_H
#define PYLOAD_DATA_STORE_H

#include <vector>

#include "../services/configuration_service.h"
#include "../net/thrift/pyload_types.h"

class PyLoadConnector;

class PyloadDataStore
{

private:
    PyloadDataStore(const PyloadDataStore& rhs);
    PyloadDataStore& operator=(const PyloadDataStore& rhs);

    PyLoadConnector* m_con;
    ConfigurationService m_cs;
    std::vector<PackageData> m_queuePackages;
    //const std::vector<PackageData> m_collectorPackages;
public:
    PyloadDataStore();
    virtual ~PyloadDataStore();

    void updateQueuePackageData();

    const std::vector<PackageData>& getQueuePackages() const {
        return m_queuePackages;
    }
};

#endif // PYLOAD_DATA_STORE_H
