#ifndef KEY_HPP
#define KEY_HPP
#include <functional>

enum KeyCondition {
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_HELD
};

struct KeyAction {
    // one key should only have one action
    KeyCondition condition;
    std::function<void()> action;
};


#endif //KEY_HPP
