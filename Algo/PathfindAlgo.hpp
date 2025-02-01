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
    virtual void findPath() {};
    void colorPath() {
        Node* node = grid->getTile(grid->endX, grid->endY).node;
        node = grid->getTile(node->parentX, node->parentY).node;
        while (node->parentX != -1 && node->parentY != -1) {
            grid->setTileType(node->tileX, node->tileY, PATH);
            node = grid->getTile(node->parentX, node->parentY).node;
        }
    };
    bool finished = false;
protected:
    virtual void addNode(int x, int y, float curScore, int parentX, int parentY) {
        static auto fn = [](const Node* a, const Node* b) {
            return a->fCost < b->fCost;
        };
        TileType type = grid->getTile(x, y).type;

        bool shouldAdd = type == EMPTY || type == END;
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

        queue.insert(std::ranges::upper_bound(queue, node, fn), node);
    };

# define diagonal 0
    virtual void extractNeighbors(const Node* node) {
        const int x = node->tileX, y = node->tileY;
        const int score = node->fCost+1;
#if diagonal
        // Add neighbors, including diagonals
        if (x > 0) {
            addNode(x - 1, y, score, x, y);
            if (y > 0) {
                addNode(x, y - 1, score, x, y);
                addNode(x - 1, y - 1, score, x, y);
            }
            if (y < grid->tilesY - 1) {
                addNode(x, y + 1, score, x, y);
                addNode(x - 1, y + 1, score, x, y);
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
};

#endif //PATHFINDALGO_HPP