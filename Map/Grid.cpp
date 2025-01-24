#include "Grid.hpp"

#include <stdexcept>

#include "../Game.hpp"
#include "../Util/Logger.hpp"

Grid::Grid(Game* game, const uint8_t width, const uint8_t height) {
    this->width = width;
    this->height = height;
    this->game = game;
    const auto d = game->getDimensions();
    const bool wider = d.first > d.second;
    tileSize = wider ? d.second / height : d.first / width; // fit mode
    padding_x = wider ? (d.first - d.second) >> 1 : 0;
    padding_y = wider ? 0 : (d.second - d.first) >> 1;

    tiles = new Tile*[width];
    for (int i = 0; i < width; i++) {
        tiles[i] = new Tile[height];
        for (int j = 0; j < height; j++) {
            tiles[i][j].isWall = false;
            tiles[i][j].rectText = {padding_x + i * tileSize, padding_y + j * tileSize, tileSize, tileSize};
        }
    }
}

Tile Grid::getTile (const uint8_t x, const uint8_t y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        Logger::err("x or y out of bound");
        throw std::out_of_range("x or y out of bound");
    }
    return tiles[x][y];
}

void Grid::draw() const {
    static SDL_Renderer* renderer = game->getRenderer();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
            if (tiles[i][j].isWall) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderDrawRect(renderer, &tiles[i][j].rectText);
        }
    }
}
