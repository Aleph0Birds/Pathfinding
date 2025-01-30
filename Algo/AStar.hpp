//
// Created by User on 2025/1/30.
//

#ifndef ASTAR_HPP
#define ASTAR_HPP
#include "PathfindAlgo.hpp"


class AStar : public PathfindAlgo {
public:
    explicit AStar(Grid* grid) : PathfindAlgo(grid) {
        int score = 0;
        queue.at(0).score = score;
    }
    void findPath() override;
protected:
    void addNode(int x, int y, int curScore, int parentX, int parentY) override;
    void extractNeighbors(const Node *node) override;
private:
    int calculateScore(int x, int y) const;
};



#endif //ASTAR_HPP
