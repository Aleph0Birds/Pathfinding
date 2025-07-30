//
// Created by User on 2025/2/3.
//

#ifndef KEYMAP_HPP
#define KEYMAP_HPP
#include <SDL_scancode.h>

struct KeyMap {
    static constexpr SDL_Scancode PAUSE = SDL_SCANCODE_SPACE;
    static constexpr SDL_Scancode UP = SDL_SCANCODE_W;
    static constexpr SDL_Scancode DOWN = SDL_SCANCODE_S;
};

#endif //KEYMAP_HPP
