#include "util.h"

#include <sstream>

#include "log.h"


int util::stringToInt(const std::string& str)
{
    LOG(TRACE) << "util::stringToInt";
    int convertedInput;
    std::istringstream inStream(str);
    inStream >> convertedInput;
    return convertedInput;
}

std::string util::intToString(const int i)
{
    LOG(TRACE) << "util:intToString";
    std::stringstream ss;
    ss << i;
    return ss.str();
}
