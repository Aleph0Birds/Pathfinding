#ifndef GRID_HPP
#define GRID_HPP
#include <cstdint>

#include "Tile.hpp"

class Game;

class Grid {
public:
    Grid(Game* game, uint8_t width, uint8_t height);
    void draw() const;

    Tile getTile(uint8_t x, uint8_t y) const;

private:
    Game* game;
    Tile** tiles;
    uint8_t width, height;
    uint8_t tileSize;
    uint8_t padding_x, padding_y;
};

#endif //GRID_HPP