//
// Created by wuqiu on 23/1/2025.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <cmath>
#include <math.h>
#include <SDL_log.h>
#include <string>

class Logger {
public:
    static void log(const char* message);
    static void log(const std::string& message);
    static void err(const std::string& message);
    static void SDL_log(const std::string& message, const char* fmt...);
};



#endif //LOGGER_HPP
