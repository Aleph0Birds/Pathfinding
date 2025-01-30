//
// Created by wuqiu on 26/1/2025.
//

#include "Dijkstra.hpp"

void Dijkstra::findPath() {
    if (queue.empty()) {
        finished = true;
        return;
    }

    const Node *node = &queue.front();
    queue.erase(queue.begin());
    TileType type = grid->getTile(node->tileX, node->tileY).type;
    if (!(type == START || type == END)) {
        grid->setTileType(node->tileX, node->tileY, EMPTY_SEARCHED);
    }
    extractNeighbors(node);
    if (finished)
        colorPath();

}
