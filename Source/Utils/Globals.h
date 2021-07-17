#ifndef _H_GLOBALS
#define _H_GLOBALS

#include <string>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define SRC std::string(std::getenv("CONICS_PATH"))
#define DEBUG 1

#endif