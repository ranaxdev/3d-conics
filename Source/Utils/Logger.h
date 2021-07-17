#ifndef _H_LOGGER
#define _H_LOGGER
#include <string>

enum lvl{
    INFO = 0,
    WARN = 1,
    ERROR = 2
};
class Logger{
public:
    Logger() = delete;

    static void log(lvl level, std::string&& msg, const char* where, uint16_t at);

private:
    static std::string str_log;
    static const char* tag[3];

};

#endif