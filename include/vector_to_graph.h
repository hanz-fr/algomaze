#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>

struct Node {
    int id;
    int row;
    int col;
};

std::map<int, std::vector<int>> buildGraph(const std::vector<std::vector<bool>>& maze_data);

#endif