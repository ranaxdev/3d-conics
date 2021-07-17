#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>

#include "Globals.h"
#include "Logger.h"


std::string Logger::str_log = "*============================= APP-LOG =============================*\n";
const char* Logger::tag[3] = {"[INFO]","[WARN]","[ERROR]"};

void Logger::log(lvl level, std::string&& msg, const char* where, uint16_t at) {
    // Logs information
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::stringstream s;
    s << std::put_time(&tm, "   %Y-%m-%d @ %H:%M:%S   ");
    s << "|" << where << ":" << at << "| ";

    msg.insert(0, s.str());
    msg.insert(0, tag[level]);
    msg.append("\n");

    str_log.append(msg);

}

void Logger::dump() {
    // Dumps log to output directory (called on harness detachment)
    std::ofstream f;
    f.open(DUMP_LOC+"log.txt");

}


