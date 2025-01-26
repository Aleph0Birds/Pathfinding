#ifndef TILE_HPP
#define TILE_HPP
#include <SDL_rect.h>

#include "TileType.hpp"

class Tile {
public:
    void draw(SDL_Renderer* renderer) const {
        uint8_t r = 0, g = 0, b = 0;
        bool fill = true;
        switch (type) {
            case EMPTY:
                r = 50; g = 200; b = 200;
                fill = false;
                break;
            case EMPTY_SEARCHED:
                r = 50; g = 150; b = 150;
                break;
            case EMPTY_EDGE:
                r = 50; g = 100; b = 100;
                break;
            case WALL:
                r = 0; g = 0; b = 0;
                break;
            case START:
                r = 0; g = 255; b = 100;
                break;
            case END:
                r = 0; g = 100; b = 255;
                break;
            default:
                r = 0, g = 0, b = 0;
                break;
        }
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawRect(renderer, &rectText);
        if (fill) SDL_RenderFillRect(renderer, &rectText);
    }
    TileType type;
    SDL_Rect rectText;
};

#endif //TILE_HPP
