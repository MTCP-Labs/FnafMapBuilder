#include "log.hpp"

void print(LOG_TYPE log_type, std::string out) {
    switch (log_type) {
        case 0:
            std::cout << "ERROR: ";
            break;
        case 1:
            std::cout << "DEBUG: ";
            break;
        case 2:
            std::cout << "INFO: ";
            break;
        case 3:
            std::cout << "INPUT: ";
            break;
        default:
            return;
    }

    std::cout << out << std::endl;
}