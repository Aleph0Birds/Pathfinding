#include "Grid.hpp"

#include <stdexcept>

#include "../Game.hpp"
#include "../Util/Logger.hpp"

Grid::Grid(Game* game, const uint8_t tilesX, const uint8_t tilesY) {
    this->game = game;
    this->tilesX = tilesX;
    this->tilesY = tilesY;
    renderer = game->getRenderer();
    constexpr int worldSizeX = Game::worldSizeX;
    constexpr int worldSizeY = Game::worldSizeY;
    const bool wider = worldSizeX > worldSizeY;
    tileSize = wider ? worldSizeY / tilesX : worldSizeX / tilesY; // fit mode
    padding_x = wider ? (worldSizeX - worldSizeY) >> 1 : 0;
    padding_y = wider ? 0 : (worldSizeY - worldSizeX) >> 1;

    tiles = new Tile*[tilesX];
    for (int i = 0; i < tilesX; i++) {
        tiles[i] = new Tile[tilesY];
        for (int j = 0; j < tilesY; j++) {
            tiles[i][j].isWall = false;
            tiles[i][j].rectText = {padding_x + i * tileSize, padding_y + j * tileSize, tileSize, tileSize};
        }
    }
}

Tile Grid::getTile (const uint8_t x, const uint8_t y) const {
    if (x < 0 || x >= tilesX || y < 0 || y >= tilesY) {
        Logger::err("x or y out of bound");
        throw std::out_of_range("x or y out of bound");
    }
    return tiles[x][y];
}

void Grid::setPadding(const uint8_t x, const uint8_t y) {
    padding_x = x;
    padding_y = y;
    for (int i = 0; i < tilesX; i++) {
        for (int j = 0; j < tilesY; j++) {
            tiles[i][j].rectText = {padding_x + i * tileSize, padding_y + j * tileSize, tileSize, tileSize};
        }
    }
}

void Grid::draw() const {
    for (int i = 0; i < tilesX; i++) {
        for (int j = 0; j < tilesY; j++) {
            if (tiles[i][j].isWall) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &tiles[i][j].rectText);
            } else {
                SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
            }
            SDL_RenderDrawRect(renderer, &tiles[i][j].rectText);
        }
    }
}
