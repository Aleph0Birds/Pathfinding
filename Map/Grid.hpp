#ifndef GRID_HPP
#define GRID_HPP
#include <cstdint>
#include <SDL_render.h>

#include "Tile.hpp"

class Game;

class Grid {
public:
    Grid(Game* game, uint8_t tilesX, uint8_t tilesY);


    void draw() const;

    Tile getTile(uint8_t x, uint8_t y) const;

    void setTileType(uint8_t x, uint8_t y, TileType type) const;

    void setPadding(uint8_t x, uint8_t y);

private:
    void checkIndex(uint8_t x, uint8_t y) const;

    Game* game;
    SDL_Renderer* renderer;
    Tile** tiles;
    uint8_t tilesX, tilesY;
    uint8_t tileSize;
    uint8_t padding_x, padding_y;
};

#endif //GRID_HPP