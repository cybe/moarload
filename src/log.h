//// Setup:
// #include "log.h"
// Logger::setPidName("main"); // optional: give the thread a name
// Logger::reportingLevel() = TRACE; // optional, standard is INFO
// FILE* log_fd = stdout; // or: FILE* log_fd = fopen("/tmp/log.txt", "w");
// FileLog::stream() = log_fd;
//
//// Logging:
// #include "log.h"
// LOG(INFO) << "important message";

#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <string>
#include <stdio.h>
#include <map>

typedef std::map<int, std::string> PidNames;

inline std::string time();
inline int getPid();

enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logIO, logTRACE};

template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& get(TLogLevel level = logINFO);
public:
    static TLogLevel& reportingLevel();
    static void setPidName(const std::string& name);
    static std::string toString(TLogLevel level);
    static TLogLevel fromString(const std::string& level);
protected:
    std::ostringstream os;
    static PidNames pidNames;
    std::string getPidName(int pid);
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::get(TLogLevel level)
{
    os << "- " << time();
    os << " <" << getPidName(getPid()) << "> ";
    os << toString(level) << ": ";
    return os;
}

template <typename T>
Log<T>::~Log()
{
    os << std::endl;
    T::output(os.str());
}

template <typename T>
TLogLevel& Log<T>::reportingLevel()
{
    static TLogLevel reportingLevel = logDEBUG;
    return reportingLevel;
}

template <typename T>
void Log<T>::setPidName(const std::string& name)
{
    pidNames[getPid()] = name;
}

template <typename T>
std::string Log<T>::toString(TLogLevel level)
{
    static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG", "IO", "TRACE"};
    return buffer[level];
}

template <typename T>
TLogLevel Log<T>::fromString(const std::string& level)
{
    switch (level)
    {
        case "TRACE" :
            return logTRACE;
        case "IO" :
            return logIO;
        case "DEBUG" :
            return logDEBUG;
        case "INFO" :
            return logINFO;
        case "WARNING" :
            return logWARNING;
        case "ERROR" :
            return logERROR;
        default :
            Log<T>().Get(logWARNING) << "Unknown logging level '" << level
                                  << "'. Using INFO level as default.";
            return logINFO;
    }
}

template <typename T>
PidNames Log<T>::pidNames = PidNames();

template <typename T>
std::string Log<T>::getPidName(int pid)
{
    if (pidNames.find(pid) != pidNames.end())
    {
        return pidNames.at(pid);
    }
    else
    {
        std::stringstream buffer;
        buffer << pid;
        return buffer.str();
    }
}

class FileLog
{
public:
    static FILE*& stream();
    static void output(const std::string& msg);
};

inline FILE*& FileLog::stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

inline void FileLog::output(const std::string& msg)
{
    FILE* pStream = stream();
    if (!pStream)
    {
        return;
    }
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   if defined (BUILDING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllexport)
#   elif defined (USING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllimport)
#   else
#       define FILELOG_DECLSPEC
#   endif // BUILDING_DBSIMPLE_DLL
#else
#   define FILELOG_DECLSPEC
#endif // _WIN32

class FILELOG_DECLSPEC Logger : public Log<FileLog> {};
//typedef Log<FileLog> Logger;

#ifndef LOG_MAX_LEVEL
#define LOG_MAX_LEVEL logTRACE
#endif

#define LOG(level) \
    if (level > LOG_MAX_LEVEL) ;\
    else if (level > Logger::reportingLevel() || !FileLog::stream()) ; \
    else Logger().get(level)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string time()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
                       "HH':'mm':'ss", buffer, MAX_LEN) == 0)
    {
        return "Error in time()";
    }

    char result[100] = {0};
    static DWORD first = GetTickCount();
    sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
    return result;
}

inline int getPid()
{
    // todo: implement. See GetCurrentProcessId:
    // http://msdn.microsoft.com/en-us/library/ms683180%28VS.85%29.aspx
    // untestet:
    // return DWORD WINAPI GetCurrentProcessId();
    return -1;
}

#else

#include <sys/time.h>

inline std::string time()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r; // = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    //sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
    sprintf(result, "%s", buffer);
    return result;
}

#include <sys/syscall.h>

inline int getPid()
{
    return syscall(SYS_gettid);
}

#endif // WIN32

#endif // LOG_H
