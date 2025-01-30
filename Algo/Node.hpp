//
// Created by wuqiu on 26/1/2025.
//

#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int tileX = -1, tileY = -1;
    int parentX = -1, parentY = -1;
    float score = 0, cost = 0;
};

#endif //NODE_HPP
