#ifndef MY_LOG_H
#define MY_LOG_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <functional>

#define COLOR_BLACK     "\033[1;30m"    // 黑色
#define COLOR_RED       "\033[1;31m"    // 红色
#define COLOR_GREEN     "\033[1;32m"    // 绿色
#define COLOR_YELLO     "\033[1;33m"    // 黄色
#define COLOR_BLUE      "\033[1;34m"    // 蓝色
#define COLOR_PURPLE    "\033[1;35m"    // 紫色
#define COLOR_CYAN      "\033[1;36m"    // 青蓝色
#define COLOR_WHITE     "\033[1;37m"    // 白色
#define COLOR_DEFAULT   "\033[m"        // 默认颜色

typedef enum
{
    LEVEL_FATAL = 1 << 0,
    LEVEL_ERROR = 1 << 1,
    LEVEL_WARNING = 1 << 2,
    LEVEL_INFO = 1 << 3,
    LEVEL_DEBUG = 1 << 4,

    LEVEL_ALL = 0xFF,
} MYLOG_LEVEL_E;

#define MYLOG_LEVEL_FATAL_MSG(fmt) \
        COLOR_RED "[FATAL] <%s>(%d): " fmt COLOR_DEFAULT "\n"
#define MYLOG_LEVEL_ERROR_MSG(fmt) \
        COLOR_RED "[ERROR] <%s>(%d): " fmt COLOR_DEFAULT "\n"
#define MYLOG_LEVEL_WARNING_MSG(fmt) \
        COLOR_YELLO "[WARNING] <%s>(%d): " fmt COLOR_DEFAULT "\n"
#define MYLOG_LEVEL_INFO_MSG(fmt) \
        COLOR_GREEN "[INFO] <%s>(%d): " fmt COLOR_DEFAULT "\n"
#define MYLOG_LEVEL_DEBUG_MSG(fmt) \
        COLOR_DEFAULT "[DEBUG] <%s>(%d): " fmt COLOR_DEFAULT "\n"

#define MYLOG_MSG(level, fmt) \
        MYLOG_ ## level ## _MSG(fmt)

#if 0
// #define MYLOG_MSG(level, fmt) \
//         if(LEVEL_FATAL == level)
//             return MYLOG_FATAL_MSG(fmt); \
//         else if(LEVEL_ERROR == level) \
//             return MYLOG_ERROR_MSG(fmt); \
//         else if(LEVEL_WARNING == level) \
//             return MYLOG_WARNING_MSG(fmt); \
//         else if(LEVEL_INFO == level) \ 
//             return MYLOG_INFO_MSG(fmt); \
//         else if(LEVEL_DEBUG == level) \
//             return MYLOG_DEBUG_MSG(fmt);
#endif

#define MYLOG(level, fmt, ...) \
        mylog::LogManager::Instance()->log(level, MYLOG_MSG(level, fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);

// #define MYLOG(level) \
//         mylog::LogManager::Instance().ostream();


namespace mylog
{
    class LogStream : public std::ostream
    {

    };

    struct LogData
    {
        LogStream stream;
    };

    class LogManager
    {
        public:
            LogManager();
            ~LogManager();
            static LogManager *Instance();
            void log(int level, const char *fmt, ...);
            void getDisplayLevel(unsigned char &displayLevel);
            void setDisplayLevel(unsigned char displayLevel);
            std::ostream &stream();

        private:
            unsigned char m_u8DisplayLevel;    // MYLOG_LEVEL_E 按位
            LogData *m_pData;
    };
}


#define CHECK_RETURN(func)                                                                   \
    do                                                                                       \
    {                                                                                        \
        ret = func;                                                                          \
        if(ret < 0)                                                                          \
            printf("%s(%d) error: function return %d!\n", __FILE__, __LINE__, ret);          \
    } while(0)


#endif
