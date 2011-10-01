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

    bool firstRun = true;
    Cookie cookie;

    std::vector<std::string>::iterator itOuter;
    for(itOuter = nameValuePairs.begin(); itOuter != nameValuePairs.end(); itOuter++)
    {
        boost::trim_left(*itOuter);

        std::vector<std::string> nameValuePair;
        boost::split(nameValuePair, *itOuter, boost::is_any_of("="));

        if (firstRun)
        {
            cookie.name = nameValuePair.at(0);
            cookie.value = nameValuePair.at(1);
            firstRun = false;
        }
        else
        {
            std::string entryName = nameValuePair.at(0);
            boost::algorithm::to_lower(entryName);

            std::map<std::string, std::string*> entries;
            entries.insert(std::pair<std::string, std::string*>("expires", &cookie.expires));
            entries.insert(std::pair<std::string, std::string*>("comment", &cookie.comment));
            entries.insert(std::pair<std::string, std::string*>("domain", &cookie.domain));
            entries.insert(std::pair<std::string, std::string*>("max-age", &cookie.maxAge));
            entries.insert(std::pair<std::string, std::string*>("path", &cookie.path));
            entries.insert(std::pair<std::string, std::string*>("secure", &cookie.secure));
            entries.insert(std::pair<std::string, std::string*>("version", &cookie.version));

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
