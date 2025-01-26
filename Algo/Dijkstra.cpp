//
// Created by wuqiu on 26/1/2025.
//

#include "Dijkstra.hpp"

void Dijkstra::findPath() {
    if (queue.empty()) return;

    const Node* node = &queue.front();
    TileType type = grid->getTile(node->tileX, node->tileY).type;
    if (!(type == START || type == END)) {
        grid->setTileType(node->tileX, node->tileY, EMPTY_SEARCHED);
    }
    extractNeighbors(node);
    if (node->tileX == grid->endX && node->tileY == grid->endY) {
        finished = true;
        colorPath();
    }
    queue.erase(queue.begin());
}

void Dijkstra::colorPath() {
    Node* node = &queue.back();
    while (node->parentX != -1 && node->parentY != -1) {
        grid->setTileType(node->tileX, node->tileY, PATH);
        node = &queue.at(node->parentX);
    }
}