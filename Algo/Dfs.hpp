//
// Created by User on 2025/1/30.
//

#ifndef DFS_HPP
#define DFS_HPP
#include "PathfindAlgo.hpp"


class DFS : public PathfindAlgo {
public:
    explicit DFS (Grid* grid) : PathfindAlgo(grid) {}
    void tickFindPath() override;
protected:
    void addNode(int x, int y, float curScore, int parentX, int parentY) override;
    //void extractNeighbors(const Node *node) override;
};



#endif //DFS_HPP
