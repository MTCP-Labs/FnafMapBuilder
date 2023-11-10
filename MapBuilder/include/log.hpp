#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <string>

typedef enum {
    LT_ERROR = 0,
    LT_DEBUG = 1,
    LT_INFO = 2,
    LT_INPUT = 3
} LOG_TYPE;

extern void print(LOG_TYPE log_type, std::string out);

#endif /* __LOG_HPP__ */