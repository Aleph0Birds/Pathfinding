//
// Created by wuqiu on 23/1/2025.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>

class Logger {
public:
    static void log(const char* message);
    static void log(const std::string& message);
    static void err(const std::string& message);
};



#endif //LOGGER_HPP
