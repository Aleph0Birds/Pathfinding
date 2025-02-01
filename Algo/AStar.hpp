//
// Created by User on 2025/1/30.
//

#ifndef ASTAR_HPP
#define ASTAR_HPP
#include "PathfindAlgo.hpp"


class AStar : public PathfindAlgo {
public:
    explicit AStar(Grid* grid) : PathfindAlgo(grid) {
        //int score = 0;
        queue.at(0)->fCost = 0;
    }
    void findPath() override;
protected:
    void addNode(int x, int y, float curScore, int parentX, int parentY) override;
    void extractNeighbors(const Node *node) override;
private:
    float calculateHCost(int x, int y, float gCost) const;
};



#endif //ASTAR_HPP
