#include "myLog.h"
#include <stdarg.h>

using namespace mylog;

LogManager::LogManager()
{
    m_u8DisplayLevel = 0;
}

LogManager::~LogManager()
{

}

LogManager *LogManager::Instance()
{
    static LogManager instance;
    return &instance;
}

void LogManager::log(int level, const char *fmt, ...)
{
    // std::string msg = MYLOG_MSG(level, fmt);
    if(0 == (m_u8DisplayLevel & level))
    {
        return;
    }
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    fflush(stdout);
    va_end(ap);
}

void LogManager::getDisplayLevel(unsigned char &displayLevel)
{
    displayLevel = m_u8DisplayLevel;
}

void LogManager::setDisplayLevel(unsigned char displayLevel)
{
    m_u8DisplayLevel = displayLevel;
}

std::ostream &LogManager::stream()
{
    return m_pData->stream;
}
