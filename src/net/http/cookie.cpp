#include "cookie.h"

#include <vector>

#include <boost/algorithm/string.hpp>

#include "../../log.h"


Cookie::Cookie()
{
    //ctor
}

Cookie::~Cookie()
{
    //dtor
}

Cookie Cookie::parse(const std::string& cookieString)
{
    std::vector<std::string> nameValuePairs;
    boost::split(nameValuePairs, cookieString, boost::is_any_of(";"));

    Cookie cookie;

    std::map<std::string, std::string*> entries;
    entries.insert(make_pair("expires", &cookie.expires));
    entries.insert(make_pair("comment", &cookie.comment));
    entries.insert(make_pair("domain", &cookie.domain));
    entries.insert(make_pair("max-age", &cookie.maxAge));
    entries.insert(make_pair("path", &cookie.path));
    entries.insert(make_pair("secure", &cookie.secure));
    entries.insert(make_pair("version", &cookie.version));

    std::vector<std::string>::iterator nameValuePairsIt;
    for (nameValuePairsIt = nameValuePairs.begin(); nameValuePairsIt != nameValuePairs.end(); nameValuePairsIt++)
    {
        boost::trim_left(*nameValuePairsIt);

        std::vector<std::string> nameValuePair;
        boost::split(nameValuePair, *nameValuePairsIt, boost::is_any_of("="));

        if (nameValuePairsIt == nameValuePairs.begin())
        {
            cookie.name = nameValuePair.at(0);
            cookie.value = nameValuePair.at(1);
        }
        else
        {
            std::string entryName = nameValuePair.at(0);
            boost::algorithm::to_lower(entryName);

            if (entries.find(entryName) != entries.end())
            {
                *(entries[entryName]) = nameValuePair.at(1);
            }
            else
            {
                LOG(logWARNING) << "unknown cookie element: " << entryName;
            }
        }
    }
    return cookie;
}

std::string Cookie::build() const
{
    return name + "=" + value;
}

bool Cookie::isValid(const std::string& path, const std::string& domain) const
{
    return true;
}
