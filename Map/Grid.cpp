#include "Grid.hpp"

#include <stdexcept>

#include "../Game.hpp"
#include "../Util/Logger.hpp"

void Grid::initMaze(const uint8_t tilesX, const uint8_t tilesY) {
    tiles = new Tile*[tilesX];
    for (int i = 0; i < tilesX; i++) {
        tiles[i] = new Tile[tilesY];
        for (int j = 0; j < tilesY; j++) {
            tiles[i][j].type = EMPTY;
            tiles[i][j].rectText = {padding_x + i * tileSize, padding_y + j * tileSize, tileSize, tileSize};
            tiles[i][j].node = new Node {i, j, -1, -1, 0};
        }
    }
}

Grid::Grid(Game* game, const uint8_t tilesX, const uint8_t tilesY) {
    this->game = game;
    this->tilesX = tilesX;
    this->tilesY = tilesY;
    renderer = game->getRenderer();
    constexpr int worldSizeX = Game::worldSizeX;
    constexpr int worldSizeY = Game::worldSizeY;
    constexpr bool wider = worldSizeX > worldSizeY;
    tileSize = wider ? worldSizeY / tilesX : worldSizeX / tilesY; // fit mode
    padding_x = wider ? (worldSizeX - worldSizeY) >> 1 : 0;
    padding_y = wider ? 0 : (worldSizeY - worldSizeX) >> 1;

    //srand(97531);

    initMaze(tilesX, tilesY);

    // set random wall
    for (int i = 0; i < tilesX; i++) {
        for (int j = 0; j < tilesY; j++) {
            if (rand() % 100 < 25) {
                tiles[i][j].type = WALL;
            }
        }
    }
    // not random start and end
    beginX = 0;// rand() % tilesX;
    beginY = tilesY-1;//rand() % tilesY;
    endX = tilesX-1;//rand() % tilesX;
    endY = 0;//rand() % tilesY;

    tiles[beginX][beginY].type = START;
    tiles[endX][endY].type = END;

    // tiles[0][16].type = WALL;
    // tiles[1][18].type = WALL;
    // tiles[2][19].type = WALL;

}

void Grid::checkIndex(const uint8_t x, const uint8_t y) const {
    if (x < 0 || x >= tilesX || y < 0 || y >= tilesY) {
        Logger::err("x or y out of bound");
        throw std::out_of_range("x or y out of bound");
    }
}

Tile Grid::getTile(const uint8_t x, const uint8_t y) const {
    checkIndex(x, y);
    return tiles[x][y];
}

void Grid::setTileType(const uint8_t x, const uint8_t y, const TileType type) const {
    checkIndex(x, y);
    tiles[x][y].type = type;
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
            tiles[i][j].draw(renderer);
        }
    }
}
