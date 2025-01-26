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
        queue.push_back({grid->beginX, grid->beginY, -1, -1, -1});
    }
    virtual void findPath() {};
    virtual void colorPath() {};
    bool finished = false;
protected:
    void addNode(int x, int y, int score, int parentX, int parentY) {
        static auto fn = [](const Node &a, const Node &b) {
            return a.score < b.score;
        };
        bool shouldAdd = grid->getTile(x, y).type == EMPTY;
        if (!shouldAdd) return;
        Node* node = new Node {x, y, parentX, parentY, score};
            grid->setTileType(x, y, EMPTY_EDGE);

        queue.insert(std::ranges::upper_bound(queue, *node, fn), *node);
    }

    void extractNeighbors(const Node* node) {
        const int x = node->tileX, y = node->tileY;
        const int score = node->score+1;
        // add X
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
    }

    Grid* grid;
    std::pmr::vector<Node> queue;
};

#endif //PATHFINDALGO_HPP