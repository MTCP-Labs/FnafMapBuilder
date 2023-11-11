#include "log.hpp"

void print(LOG_TYPE log_type, std::string out) {
    switch (log_type) {
        case LT_ERROR:
            std::cout << "ERROR: ";
            break;
        case LT_DEBUG:
            std::cout << "DEBUG: ";
            break;
        case LT_INFO:
            std::cout << "INFO: ";
            break;
        case LT_INPUT:
            std::cout << "INPUT: ";
            break;
        default:
            return;
    }

    std::cout << out << std::endl;
}