#include "util.h"

#include <sstream>

#include "log.h"


int util::stringToInt(const std::string& str)
{
    int convertedInput;
    std::istringstream inStream(str);
    inStream >> convertedInput;
    return convertedInput;
}

std::string util::intToString(const int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
