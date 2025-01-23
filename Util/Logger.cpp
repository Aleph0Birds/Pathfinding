//
// Created by wuqiu on 23/1/2025.
//

#include "Logger.hpp"
#include <iostream>
using namespace std;

#define nl '\n'

void Logger::log(const char *message) {
    cout << message << nl;
}

void Logger::log(const std::string& message) {
    cout << message << nl;
}

