//
// Created by User on 2025/1/30.
//

#include "AStar.hpp"

#include <complex>
#include <deque>

void AStar::tickFindPath() {
    if (queue.empty()) {
        end(false);
        return;
    }
    const Node* node = queue.front();
    queue.erase(queue.begin());
    TileType type = grid->getTile(node->tileX, node->tileY).type;
    if (!(type == START || type == END)) {
        grid->setTileType(node->tileX, node->tileY, EMPTY_SEARCHED);
    }
    extractNeighbors(node);
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

void AStar::addNode(int x, int y, float parentScore, int parentX, int parentY) {
    const TileType type = grid->getTile(x, y).type;
    const float gCost = parentScore+1;

    const bool shouldAdd = type == EMPTY || type == END ||
        type == EMPTY_TOBECHECK || type == EMPTY_SEARCHED;
    if (!shouldAdd) return;
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

    if (type == EMPTY_SEARCHED)
        return;

    Node *node = grid->getTile(x, y).node;
    node->tileX = x;
    node->tileY = y;
    node->gCost = gCost;
    node->hCost = calculateHCost(x, y, gCost);
    node->fCost = gCost + node->hCost;
    node->parentX = parentX;
    node->parentY = parentY;
    if (type == END) {
        end(true);
        return;
    }
    grid->setTileType(x, y, EMPTY_TOBECHECK);
    queue.insert(std::ranges::lower_bound(queue, node, fn), node);
    this->totalSearches++;
}


