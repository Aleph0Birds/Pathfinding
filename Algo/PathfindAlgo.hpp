//
// Created by wuqiu on 26/1/2025.
//

#ifndef PATHFINDALGO_HPP
#define PATHFINDALGO_HPP
#include <algorithm>
#include <vector>

#include "Node.hpp"
#include "../Map/Grid.hpp"

class Grid;

class PathfindAlgo {
public:
    virtual ~PathfindAlgo() {
        queue.clear();
    }

    explicit PathfindAlgo(Grid* grid) : grid(grid) {
        //queue.reserve(grid->tilesX * grid->tilesY);
        queue.push_back(grid->getTile(grid->beginX, grid->beginY).node);
    }
    virtual void tickFindPath() {};
    void colorPath() {
        Node* node = grid->getTile(grid->endX, grid->endY).node;
        node = grid->getTile(node->parentX, node->parentY).node;
        while (node->parentX != -1 && node->parentY != -1) {
            this->pathLength++;
            grid->setTileType(node->tileX, node->tileY, PATH);
            node = grid->getTile(node->parentX, node->parentY).node;
        }
    };
    bool finished = false;
protected:
    virtual void addNode(int x, int y, float curScore, int parentX, int parentY) {
        TileType type = grid->getTile(x, y).type;

        const bool shouldAdd = type == EMPTY || type == END;
        if (!shouldAdd) return;
        Node *node = grid->getTile(x, y).node;
        node->tileX = x;
        node->tileY = y;
        node->fCost = curScore;
        node->parentX = parentX;
        node->parentY = parentY;
        if (type == END) {
            finished = true;
        }
        else
            grid->setTileType(x, y, EMPTY_TOBECHECK);

        queue.push_back(node);
    };

# define diagonal 0
    virtual void extractNeighbors(const Node* node) {
        static const std::pair<char, char> dirs[8] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };
        const int x = node->tileX, y = node->tileY;
        const float score = node->gCost;
#if diagonal
        for (char i = 0; i < 8; i++) {
            std::pair<char, char> dir = dirs[i];
            int extractX = x + dir.first, extractY = y + dir.second;
            if (isValidCellToAdd(extractX, extractY, x, y)) {
                addNode(extractX, extractY, score + (dir.first != 0 && dir.second != 0 ? 0.44f : 0.f), x, y);
            }
        }

        if (x < grid->tilesX - 1) {
            addNode(x + 1, y, score, x, y);
            if (y > 0) {
                addNode(x + 1, y - 1, score, x, y);
                addNode(x + 1, y, score, x, y);
            }
            if (y < grid->tilesY - 1) {
                addNode(x + 1, y + 1, score, x, y);
                addNode(x, y + 1, score, x, y);
            }
        }
# else
        // Add neighbors
        if (x > 0) {
            addNode(x - 1, y, score, x, y);
        }
        if (x < grid->tilesX - 1) {
            addNode(x + 1, y, score, x, y);
        }
        if (y > 0) {
            addNode(x, y - 1, score, x, y);
        }
        if (y < grid->tilesY - 1) {
            addNode(x, y + 1, score, x, y);
        }
# endif
    }

    Grid* grid;
    std::pmr::vector<Node*> queue;
    unsigned int totalSearches = 0;
    unsigned int pathLength = 0;
    void end(const bool found) {
        finished = true;

        if (found)
            colorPath();

        Logger::log("Pathfinding finished: " + std::string(found ? "Found" : "Not Found"));
        Logger::log("Queue size: " + std::to_string(queue.size()));
        Logger::log("Queue capacity: " + std::to_string(queue.capacity()));
        Logger::log("Path length: " + std::to_string(pathLength));
        Logger::log("Total searches: " + std::to_string(totalSearches));
    }
private:
    bool isValidCellToAdd(int x, int y, int parentX, int parentY) const {
        if (x < 0 || x >= grid->tilesX || y < 0 || y >= grid->tilesY) return false;
        if (grid->getTile(x, y).type == WALL) return false;
        if (grid->getTile(x, parentY).type == WALL &&
            grid->getTile(parentX, y).type == WALL)
            return false;
        return true;
    }
};

#endif //PATHFINDALGO_HPP