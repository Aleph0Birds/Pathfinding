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
                fill = false;
                break;
            case EMPTY_SEARCHED:
                r = 50; g = 200; b = 200;
                break;
            case EMPTY_EDGE:
                r = 170; g = 170; b = 170;
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
            case PATH:
                r = 255; g = 255; b = 0;
                break;
            default:
                r = 0, g = 0, b = 0;
                break;
        }
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        if (fill) SDL_RenderFillRect(renderer, &rectText);
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderDrawRect(renderer, &rectText);
    }
    TileType type;
    SDL_Rect rectText;
};

#endif //TILE_HPP
