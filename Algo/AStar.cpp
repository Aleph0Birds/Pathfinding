//
// Created by User on 2025/1/30.
//

#include "AStar.hpp"

#include <complex>
#include <deque>

void AStar::findPath() {
    if (queue.empty()) {
        finished = true;
        return;
    }
    const Node nodeV = queue.front();
    queue.erase(queue.begin());
    const Node* node = &nodeV;
    TileType type = grid->getTile(node->tileX, node->tileY).type;
    if (!(type == START || type == END)) {
        grid->setTileType(node->tileX, node->tileY, EMPTY_SEARCHED);
    }
    extractNeighbors(node);
    if (finished)
        colorPath();
}

void AStar::extractNeighbors(const Node *node) {
    const int x = node->tileX, y = node->tileY;
    const float parentCost = node->cost;
    // Add neighbors
    if (x > 0) {
        addNode(x - 1, y, calculateScore(x-1,y, parentCost), x, y);
    }
    if (x < grid->tilesX - 1) {
        addNode(x + 1, y, calculateScore(x+1,y, parentCost), x, y);
    }
    if (y > 0) {
        addNode(x, y - 1, calculateScore(x,y-1, parentCost), x, y);
    }
    if (y < grid->tilesY - 1) {
        addNode(x, y + 1, calculateScore(x,y+1, parentCost), x, y);
    }
}

float AStar::calculateScore(const int x, const int y, const float parentCost) const {
    //const int scoreBegin = std::abs(x - grid->beginX) +
    //    std::abs(y - grid->beginY);
    const int scoreEnd = std::abs(x - grid->endX) +
        std::abs(y - grid->endY);
    return parentCost + scoreEnd;
}

void AStar::addNode(int x, int y, float curScore, int parentX, int parentY) {
    TileType type = grid->getTile(x, y).type;

    bool shouldAdd = type == EMPTY || type == END;
    if (!shouldAdd) return;
    //const int costScore = grid->getTile(parentX, parentY).node->score;

    static auto fn = [](const Node &a, const Node &b) {
        return a.score < b.score;
    };
    Node *node = grid->getTile(x, y).node;
    node->tileX = x;
    node->tileY = y;
    node->score = curScore;
    node->cost = grid->getTile(parentX, parentY).node->cost+1;
    node->parentX = parentX;
    node->parentY = parentY;
    if (type == END) {
        finished = true;
        return;
    }
    grid->setTileType(x, y, EMPTY_TOBECHECK);

    queue.insert(std::ranges::lower_bound(queue, *node, fn), *node);
}


