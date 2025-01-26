//
// Created by wuqiu on 26/1/2025.
//

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "PathfindAlgo.hpp"


class Dijkstra : public PathfindAlgo {
public:
    explicit Dijkstra(Grid* grid) : PathfindAlgo(grid) {}
    void findPath() override;

    void colorPath() override;
};



#endif //DIJKSTRA_HPP
