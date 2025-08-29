#include "Grid.hpp"

#include <ctime>
#include <stdexcept>

#include "../Game.hpp"
#include "../Util/Logger.hpp"

void Grid::initMaze(const TileType initType) {
    tiles = new Tile*[tilesX];
    for (int i = 0; i < tilesX; i++) {
        tiles[i] = new Tile[tilesY];
        for (int j = 0; j < tilesY; j++) {
            tiles[i][j].type = initType;
            tiles[i][j].rectText = {padding_x + i * tileSize, padding_y + j * tileSize, tileSize, tileSize};
            tiles[i][j].node = new Node {i, j, -1, -1, 0};
        }
    }
}

void Grid::generateMaze(const int startX, const int startY) const {
    // generate maze using prim's algorithm

    // startss from a random cell
    tiles[startX][startY].type = EMPTY;
    std::vector<std::pair<int, int>> walls;
    walls.push_back({startX, startY});
    while (!walls.empty()) {
        int index = rand() % walls.size();
        int x = walls[index].first;
        int y = walls[index].second;
        walls.erase(walls.begin() + index);
        if (x > 1 && tiles[x - 2][y].type == WALL) {
            tiles[x - 2][y].type = EMPTY;
            tiles[x - 1][y].type = EMPTY;
            walls.push_back({x - 2, y});
        }
        if (x < tilesX - 2 && tiles[x + 2][y].type == WALL) {
            tiles[x + 2][y].type = EMPTY;
            tiles[x + 1][y].type = EMPTY;
            walls.push_back({x + 2, y});
        }
        if (y > 1 && tiles[x][y - 2].type == WALL) {
            tiles[x][y - 2].type = EMPTY;
            tiles[x][y - 1].type = EMPTY;
            walls.push_back({x, y - 2});
        }
        if (y < tilesY - 2 && tiles[x][y + 2].type == WALL) {
            tiles[x][y + 2].type = EMPTY;
            tiles[x][y + 1].type = EMPTY;
            walls.push_back({x, y + 2});
        }
    }
}

void Grid::randomWall() const {
    // set random wall
    for (int i = 0; i < tilesX; i++) {
        for (int j = 0; j < tilesY; j++) {
            if (rand() % 100 < 25) {
                tiles[i][j].type = WALL;
            }
        }
    }
}


void Grid::genMazeRandom() {

    const unsigned int seed = time(NULL);
    srand(seed);
    Logger::log("Random seed: " + std::to_string(seed));

    initMaze(EMPTY);
    // not random start and end
    beginX = rand() % this->tilesX;
    beginY = rand() % this->tilesY;
    endX = tilesX-2;//rand() % tilesX;
    endY = 1;//rand() % tilesY;
    //generateMaze(beginX, beginY);
    randomWall();
    tiles[beginX][beginY].type = START;
    tiles[endX][endY].type = END;
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

    genMazeRandom();
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
