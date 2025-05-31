#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <map>
#include <limits> 

std::vector<int> findShortestPathDijkstra(
    const std::map<int, std::vector<int>>& graph,
    int start_node_id,
    int end_node_id
);

#endif