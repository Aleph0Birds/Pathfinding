//
// Created by wuqiu on 26/1/2025.
//

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "PathfindAlgo.hpp"

/**
 * BFS basically
 */
class Dijkstra : public PathfindAlgo {
public:
    explicit Dijkstra(Grid* grid) : PathfindAlgo(grid) {}
    void tickFindPath() override;
};

#endif //DIJKSTRA_HPP