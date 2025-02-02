#ifndef GRID_HPP
#define GRID_HPP
#include <cstdint>
#include <SDL_render.h>

#include "Tile.hpp"

class Game;

class Grid {
public:
    void initMaze(TileType initType);

    void generateMaze(int startX, int startY) const;
    void randomMaze() const;

    Grid(Game* game, uint8_t tilesX, uint8_t tilesY);

    void draw() const;

    void setTileType(uint8_t x, uint8_t y, TileType type) const;
    void setPadding(uint8_t x, uint8_t y);
    Tile getTile(uint8_t x, uint8_t y) const;
    int beginX = 0, beginY;
    int endX, endY = 0;
    uint8_t tilesX, tilesY;

private:
    void checkIndex(uint8_t x, uint8_t y) const;

    Game* game;
    SDL_Renderer* renderer;
    Tile** tiles;
    uint8_t tileSize;
    uint8_t padding_x, padding_y;
};

#endif //GRID_HPP