//
// Created by wuqiu on 26/1/2025.
//

#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int tileX = -1, tileY = -1;
    int parentX = -1, parentY = -1;
    float fCost = 0, gCost = 0, hCost = 0;

    bool operator > (const Node& other) const {
        return fCost > other.fCost;
    }
};

#endif //NODE_HPP
