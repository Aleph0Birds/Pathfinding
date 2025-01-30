//
// Created by User on 2025/1/30.
//

#include "Dfs.hpp"

void DFS::findPath() {
    if (queue.empty()) {
        finished = true;
        return;
    }

    Node* node = &queue.back();
    queue.erase(queue.end());
    TileType type = grid->getTile(node->tileX, node->tileY).type;
    if (!(type == START || type == END)) {
        grid->setTileType(node->tileX, node->tileY, EMPTY_SEARCHED);
    }
    extractNeighbors(node);
    if (finished)
        colorPath();

}

void DFS::addNode(int x, int y, int curScore, int parentX, int parentY) {
    const TileType type = grid->getTile(x, y).type;
    const bool shouldAdd = type == EMPTY || type == END;
    if (!shouldAdd) return;
    Node *node = grid->getTile(x, y).node;
    node->tileX = x;
    node->tileY = y;
    node->score = curScore;
    node->parentX = parentX;
    node->parentY = parentY;
    if (type == END) {
        finished = true;
        return;
    }
    grid->setTileType(x, y, EMPTY_TOBECHECK);

    queue.push_back(*node);
}


