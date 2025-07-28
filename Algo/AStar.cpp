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
    const Node* node = queue.front();
    queue.erase(queue.begin());
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
    const float parentCost = node->gCost;
    // Add neighbors
    if (x > 0) {
        addNode(x - 1, y, parentCost, x, y);
    }
    if (y > 0) {
        addNode(x, y - 1, parentCost, x, y);
    }
    if (x < grid->tilesX - 1) {
        addNode(x + 1, y, parentCost, x, y);
    }
    if (y < grid->tilesY - 1) {
        addNode(x, y + 1, parentCost, x, y);
    }
}

float AStar::calculateHCost(const int x, const int y, const float gCost) const {
    // Manhattan Distance
    const int hCostLinear = std::abs(x - grid->endX) + std::abs(y - grid->endY);
    // Euclidean Distance
    //const float hCostEuclidean = std::sqrt(std::pow(x - grid->endX, 2) + std::pow(y - grid->endY, 2));
    // Chebyshev Distance
    //const int hCostChebyshev = std::max(std::abs(x - grid->endX), std::abs(y - grid->endY));
    // Weighted Heuristic: Blend Manhattan and Chebyshev distances
    //const float weightManhattan = 1.0f;
    //const float weightChebyshev = 0.5f; // Give diagonal movement a slight preference

    return hCostLinear;
}

static auto fn = [](const Node* a, const Node* b) {
    return a->fCost < b->fCost;
};

void AStar::addNode(int x, int y, float curScore, int parentX, int parentY) {
    TileType type = grid->getTile(x, y).type;
    const float gCost = curScore+1;

    const bool ignore = type == START || type == WALL || type == EMPTY_SEARCHED;
    if (ignore) return;
    //const int costScore = grid->getTile(parentX, parentY).node->score;
    auto index = std::ranges::find(queue, grid->getTile(x, y).node);
    // exists in list
    if (index != queue.end()) {
        if (Node* node = *index; gCost < node->gCost) {
            queue.erase(index);
            node->gCost = gCost;
            node->fCost = gCost + node->hCost;
            node->parentX = parentX;
            node->parentY = parentY;

            queue.insert(std::ranges::lower_bound(queue, node, fn), node);
        }
        return;
    }

    Node *node = grid->getTile(x, y).node;
    node->tileX = x;
    node->tileY = y;
    node->gCost = gCost;
    node->hCost = calculateHCost(x, y, gCost);
    node->fCost = gCost + node->hCost;
    node->parentX = parentX;
    node->parentY = parentY;
    if (type == END) {
        finished = true;
        return;
    }
    grid->setTileType(x, y, EMPTY_TOBECHECK);
    queue.insert(std::ranges::lower_bound(queue, node, fn), node);
}


